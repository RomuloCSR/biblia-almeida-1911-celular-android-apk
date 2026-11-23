#include <jni.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

extern "C" {
    extern const char *pastas_at[39];
    extern const char *pastas_nt[27];
    extern const char *nomes_at[39];
    extern const char *nomes_nt[27];
    extern const int capitulos_at[39];
    extern const int capitulos_nt[27];

    void limpar_texto_verso(const char *origem, char *destino);
    void atualizar_ortografia(char *texto);
}

#define MAX_LINHA_JNI 8192

extern "C" JNIEXPORT jobjectArray JNICALL
Java_br_com_romulocsr_biblia1911_MainActivity_obterListaLivrosJNI(
        JNIEnv *env,
        jobject /* this */,
        jint testamento) {
    int total = (testamento == 1) ? 39 : 27;
    const char **nomes = (testamento == 1) ? nomes_at : nomes_nt;

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray resultado = env->NewObjectArray(total, stringClass, env->NewStringUTF(""));

    for (int i = 0; i < total; i++) {
        env->SetObjectArrayElement(resultado, i, env->NewStringUTF(nomes[i]));
    }
    return resultado;
}

extern "C" JNIEXPORT jint JNICALL
Java_br_com_romulocsr_biblia1911_MainActivity_obterTotalCapitulosJNI(
        JNIEnv *env,
        jobject /* this */,
        jint testamento,
        jint indiceLivro) {
    if (testamento == 1 && indiceLivro >= 0 && indiceLivro < 39) {
        return capitulos_at[indiceLivro];
    }
    if (testamento == 2 && indiceLivro >= 0 && indiceLivro < 27) {
        return capitulos_nt[indiceLivro];
    }
    return 0;
}

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

    const char *pasta = nullptr;
    if (testamento == 1 && indiceLivro >= 0 && indiceLivro < 39) {
        pasta = pastas_at[indiceLivro];
    } else if (testamento == 2 && indiceLivro >= 0 && indiceLivro < 27) {
        pasta = pastas_nt[indiceLivro];
    } else {
        return env->NewStringUTF("Livro inválido.");
    }

    char caminho[256];
    snprintf(caminho, sizeof(caminho), "%s/%02d.md", pasta, capitulo);
    AAsset *asset = AAssetManager_open(mgr, caminho, AASSET_MODE_BUFFER);

    if (asset == nullptr) {
        snprintf(caminho, sizeof(caminho), "%s/%03d.md", pasta, capitulo);
        asset = AAssetManager_open(mgr, caminho, AASSET_MODE_BUFFER);
    }

    if (asset == nullptr) {
        std::string msg = "Não foi possível abrir o arquivo: " + std::string(caminho);
        return env->NewStringUTF(msg.c_str());
    }

    off_t tamanho = AAsset_getLength(asset);
    std::vector<char> conteudo(tamanho + 1, '\0');
    AAsset_read(asset, conteudo.data(), tamanho);
    AAsset_close(asset);

    std::string saida;
    saida.reserve(tamanho + 2048);

    char linha[MAX_LINHA_JNI];
    char texto_limpo[MAX_LINHA_JNI];

    const char *cursor = conteudo.data();
    while (*cursor != '\0') {
        const char *fim_linha = strchr(cursor, '\n');
        size_t len = (fim_linha != nullptr) ? (size_t)(fim_linha - cursor) : strlen(cursor);
        if (len >= MAX_LINHA_JNI - 1) len = MAX_LINHA_JNI - 2;

        memcpy(linha, cursor, len);
        linha[len] = '\0';

        cursor = (fim_linha != nullptr) ? (fim_linha + 1) : (cursor + len);

        if (strncmp(linha, "---", 3) == 0) {
            break;
        }
        if (linha[0] == '#' || linha[0] == '[') {
            continue;
        }

        int idx = 0;
        while (linha[idx] == '*' || linha[idx] == ' ') {
            idx++;
        }

        if (linha[idx] >= '1' && linha[idx] <= '9') {
            char versiculo_num[20];
            int v_pos = 0;
            while (linha[idx] >= '0' && linha[idx] <= '9' && v_pos < 19) {
                versiculo_num[v_pos++] = linha[idx++];
            }
            versiculo_num[v_pos] = '\0';

            while (linha[idx] == '*' || linha[idx] == ' ') {
                idx++;
            }

            limpar_texto_verso(&linha[idx], texto_limpo);
            atualizar_ortografia(texto_limpo);

            saida += "[";
            saida += versiculo_num;
            saida += "] ";
            saida += texto_limpo;
            saida += "\n\n";
        } else if (strncmp(linha, "**", 2) == 0 && linha[idx] != '\0' && linha[idx] != '\n' && linha[idx] != '\r') {
            limpar_texto_verso(&linha[idx], texto_limpo);
            atualizar_ortografia(texto_limpo);

            saida += "(";
            saida += texto_limpo;
            saida += ")\n\n";
        }
    }

    return env->NewStringUTF(saida.c_str());
}
