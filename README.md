# Bíblia Almeida ARC-1911 (Edição 11/2026) — Android

## 📥 [BAIXAR O APLICATIVO (toque aqui)](https://github.com/RomuloCSR/biblia-almeida-1911-celular-android-apk/releases/latest/download/BibliaAlmeida1911.apk)

**Gratuito • Sem anúncios • Funciona sem internet • Sempre a versão mais nova**

Ou aponte a câmera do celular para o código abaixo:

<img src="docs/qr-baixar-apk.png" alt="QR code para baixar o aplicativo" width="200">

**Instalar em 3 passos:**

1. Toque em **BAIXAR O APLICATIVO** acima (ou leia o QR code). O arquivo `BibliaAlmeida1911.apk` será baixado.
2. Abra o arquivo baixado (pela notificação ou pela pasta *Downloads*).
3. Se o Android pedir, toque em **Configurações** → **Permitir desta fonte** → **Instalar**.

> Já tem o aplicativo? É só baixar e instalar de novo por cima. Não precisa desinstalar.

**Compartilhe com quem precisa:** copie e envie este link pelo WhatsApp:

```
https://github.com/RomuloCSR/biblia-almeida-1911-celular-android-apk/releases/latest/download/BibliaAlmeida1911.apk
```

---

Aplicativo Android nativo, leve e **100% offline**, desenvolvido com motor de processamento e atualização ortográfica em **linguagem C pura** (`motor.biblia.c`) integrado via JNI a uma interface limpa em **Kotlin** .

> **Nota editorial:** O conteúdo está em processo contínuo de atualização e pode eventualmente apresentar pequenas falhas ortográficas ou gramaticais. Colabore nos enviando seu feedback pela aba **Issues** deste repositório. Obrigado!   

## Destaques da Edição

* **Texto Base:** Almeida Revista e Corrigida (ARC-1911, Domínio Público) com **atualização ortográfica e gramatical (Edição 11/2026)**  .
* **100% Offline e Sem Anúncios:** Todos os 66 livros (Antigo e Novo Testamento) acompanham o aplicativo, sem depender de internet .
* **Motor Nativo em C (`motor.biblia.c`):** Leitura instantânea de capítulos, limpeza de marcações e atualização ortográfica executadas diretamente em código nativo compilado via Android NDK/CMake .
* **Leitura Confortável e Compartilhamento:** Controle rápido de tamanho de fonte (`A-` / `A+`), seleção de versículos e compartilhamento completo de capítulos com referência e créditos da edição .

## Instalação Direta no Android (.APK)

1. Toque no link **[BAIXAR O APLICATIVO](https://github.com/RomuloCSR/biblia-almeida-1911-celular-android-apk/releases/latest/download/BibliaAlmeida1911.apk)** no seu celular. O arquivo **`BibliaAlmeida1911.apk`** é baixado direto, sempre na versão mais nova. (As versões anteriores ficam na aba **[Releases](https://github.com/RomuloCSR/biblia-almeida-1911-celular-android-apk/releases)**.)
2. Toque no arquivo baixado na barra de notificações ou na pasta *Downloads* do seu smartphone Android .
3. Caso o Android solicite permissão para instalar aplicativos fora da Play Store, toque em **Configurações**, ative **Permitir desta fonte** e confirme em **Instalar** (ou **Instalar assim mesmo**, caso o Google Play Protect exiba o aviso padrão de aplicativo independente).

## Este aplicativo é seguro? (Sobre alertas de segurança do sistema)

**Sim, 100% seguro.** Este é um projeto independente, gratuito e sem fins lucrativos, publicado em código aberto no **GitHub** (plataforma de referência mundial utilizada por desenvolvedores)   .

* **Por que o Android exibe alerta ao instalar um arquivo `.apk`?** O Android emite um aviso preventivo para qualquer aplicativo que não esteja publicado na loja oficial (Google Play). É um aviso padrão, e não significa que o aplicativo tenha problema.
* **Transparência total (Código Aberto):** Todo o código-fonte deste aplicativo (`motor.biblia.c`, `native-lib.cpp`, `MainActivity.kt`) e os textos dos 66 livros estão abertos e visíveis nesta página  . Qualquer técnico ou programador pode inspecionar o código e confirmar que não há coleta de dados, rastreamento ou arquivos maliciosos   .

## Estrutura do Projeto

* `app/src/main/assets/` — Base textual completa dos 66 livros em Markdown 
* `app/src/main/cpp/motor.biblia.c` — Núcleo portátil em C (tabelas, parser e ortografia) 
* `app/src/main/cpp/native-lib.cpp` — Ponte JNI entre C/AssetManager e Kotlin 
* `app/src/main/java/br/com/romulocsr/biblia1911/MainActivity.kt` — Interface Android e navegação 
* `releases/BibliaAlmeida1911.apk` — Pacote instalável pronto para distribuição 

## Autor, Colaboração e Licença

* **Autor:** Romulo CSR ([github.com/RomuloCSR](https://github.com/RomuloCSR)) — projeto de código aberto com o propósito de oferecer acesso livre, gratuito e fiel às Escrituras em dispositivos móveis  .
* **Apoio espontâneo via PIX:** `21980934118`   
 
