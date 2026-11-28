/* =============================================================================
 * native-lib.cpp — ponte JNI entre o app Android (MainActivity.kt) e o kernel C
 *
 * O que faz: entrega ao Kotlin a lista de livros, o total de capítulos e o texto
 *            de um capítulo, já com a ortografia atualizada.
 * Por quê:   desde 28/11/2026 o app usa o kernel da Bíblia (pasta kernel/), o mesmo
 *            texto do motor.biblia.c, cerca de 12 vezes mais rápido. Antes havia aqui
 *            uma cópia própria do motor e do laço de leitura.
 * Fonte:     kernel/biblia_kernel.h (API 1.0). As regras de ortografia são editadas
 *            no motor.biblia.c e o kernel é gerado de novo (veja kernel/LEIAME.md).
 * Regra:     os arquivos .md (assets/) nunca são alterados; só lidos.
 * ============================================================================= */
#include <jni.h>
#include <string>
#include <vector>
#include <cstdio>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "kernel/biblia_kernel.h"

/* ---------------------------------------------------------------------------
 * 1. TESTAMENTO + ÍNDICE  ->  LIVRO DO KERNEL
 *    O Kotlin conta os livros por testamento (AT 0..38, NT 0..26).
 *    O kernel conta de 0 a 65 (0..38 = AT, 39..65 = NT).
 *    Devolve -1 se o pedido estiver fora da faixa.
 * --------------------------------------------------------------------------- */
static int livro_kernel(jint testamento, jint indice) {
    if (testamento == 1 && indice >= 0 && indice < 39) return (int)indice;
    if (testamento == 2 && indice >= 0 && indice < 27) return 39 + (int)indice;
    return -1;
}

/* ---------------------------------------------------------------------------
 * 2. LISTA DE LIVROS DE UM TESTAMENTO ("Gênesis" ... ou "Mateus" ...)
 * --------------------------------------------------------------------------- */
extern "C" JNIEXPORT jobjectArray JNICALL
Java_br_com_romulocsr_biblia1911_MainActivity_obterListaLivrosJNI(
        JNIEnv *env,
        jobject /* this */,
        jint testamento) {
    int total = (testamento == 1) ? 39 : 27;
    int primeiro = (testamento == 1) ? 0 : 39;

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray resultado = env->NewObjectArray(total, stringClass, env->NewStringUTF(""));

    for (int i = 0; i < total; i++) {
        const char *nome = bk_livro_nome(primeiro + i);
        env->SetObjectArrayElement(resultado, i, env->NewStringUTF(nome ? nome : ""));
    }
    return resultado;
}

/* ---------------------------------------------------------------------------
 * 3. TOTAL DE CAPÍTULOS DE UM LIVRO (0 se o livro não existe)
 * --------------------------------------------------------------------------- */
extern "C" JNIEXPORT jint JNICALL
Java_br_com_romulocsr_biblia1911_MainActivity_obterTotalCapitulosJNI(
        JNIEnv *env,
        jobject /* this */,
        jint testamento,
        jint indiceLivro) {
    int livro = livro_kernel(testamento, indiceLivro);
    if (livro < 0) return 0;
    int caps = bk_livro_capitulos(livro);
    return (caps > 0) ? caps : 0;
}

/* ---------------------------------------------------------------------------
 * 4. MONTAGEM DO TEXTO DO CAPÍTULO
 *    O kernel chama esta função para cada item, na ordem do arquivo.
 *    Verso:     "[12] texto"     Subtítulo: "(texto)"
 *    Cada item termina com uma linha em branco (mesmo visual de antes).
 * --------------------------------------------------------------------------- */
static int item_texto(void *ctx, int tipo, int numero, const char *texto, size_t tamanho_texto) {
    std::string *saida = static_cast<std::string *>(ctx);
    if (tipo == BK_VERSO) {
        char num[16];
        snprintf(num, sizeof(num), "[%d] ", numero);
        *saida += num;
        saida->append(texto, tamanho_texto);
    } else {
        *saida += "(";
        saida->append(texto, tamanho_texto);
        *saida += ")";
    }
    *saida += "\n\n";
    return 0; /* 0 = continuar */
}

/* ---------------------------------------------------------------------------
 * 5. LEITURA DE UM CAPÍTULO
 *    Abre o .md dentro do APK (assets), tentando "01.md" e depois "001.md"
 *    (Salmos), entrega o conteúdo ao kernel e devolve o texto pronto.
 * --------------------------------------------------------------------------- */
extern "C" JNIEXPORT jstring JNICALL
Java_br_com_romulocsr_biblia1911_MainActivity_lerCapituloJNI(
        JNIEnv *env,
        jobject /* this */,
        jobject assetManagerObj,
        jint testamento,
        jint indiceLivro,
        jint capitulo) {
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManagerObj);
    if (mgr == nullptr) {
        return env->NewStringUTF("Erro interno: AssetManager indisponível.");
    }

    int livro = livro_kernel(testamento, indiceLivro);
    if (livro < 0) {
        return env->NewStringUTF("Livro inválido.");
    }

    /* 5.1 Abre o arquivo do capítulo (duas formas de nome) */
    char caminho[256] = "";
    AAsset *asset = nullptr;
    for (int tentativa = 0; tentativa < 2 && asset == nullptr; tentativa++) {
        if (bk_caminho_capitulo(livro, (int)capitulo, tentativa, caminho, sizeof(caminho)) < 0) {
            return env->NewStringUTF("Capítulo inválido.");
        }
        asset = AAssetManager_open(mgr, caminho, AASSET_MODE_BUFFER);
    }
    if (asset == nullptr) {
        std::string msg = "Não foi possível abrir o arquivo: " + std::string(caminho);
        return env->NewStringUTF(msg.c_str());
    }

    /* 5.2 Copia o conteúdo para a memória e fecha o arquivo */
    off_t tamanho = AAsset_getLength(asset);
    std::vector<char> conteudo((size_t)tamanho + 1, '\0');
    int lidos = AAsset_read(asset, conteudo.data(), (size_t)tamanho);
    AAsset_close(asset);
    if (lidos < 0) lidos = 0;

    /* 5.3 O kernel limpa o Markdown e atualiza a ortografia de cada item */
    std::string saida;
    saida.reserve((size_t)lidos + 2048);
    bk_capitulo(conteudo.data(), (size_t)lidos, item_texto, &saida);

    return env->NewStringUTF(saida.c_str());
}
