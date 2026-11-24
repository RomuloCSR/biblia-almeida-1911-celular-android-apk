# Bíblia Almeida ARC-1911 (Edição 11/2026) — Android

Aplicativo Android nativo, leve e **100% offline**, desenvolvido com motor de processamento e atualização ortográfica em **linguagem C pura** (`motor.biblia.c`) integrado via JNI a uma interface limpa em **Kotlin**[cite: 11].

> **Nota editorial:** O conteúdo está em processo contínuo de atualização e pode eventualmente apresentar pequenas falhas ortográficas ou gramaticais. Colabore nos enviando seu feedback pela aba **Issues** deste repositório. Obrigado![cite: 12]

## Destaques da Edição

* **Texto Base:** Almeida Revista e Corrigida (ARC-1911, Domínio Público) com **atualização ortográfica e gramatical (Edição 11/2026)**[cite: 11, 12].
* **100% Offline e Sem Anúncios:** Todos os 66 livros (Antigo e Novo Testamento) acompanham o aplicativo, sem depender de internet[cite: 11].
* **Motor Nativo em C (`motor.biblia.c`):** Leitura instantânea de capítulos, limpeza de marcações e atualização ortográfica executadas diretamente em código nativo compilado via Android NDK/CMake[cite: 11].
* **Leitura Confortável e Compartilhamento:** Controle rápido de tamanho de fonte (`A-` / `A+`), seleção de versículos e compartilhamento completo de capítulos com referência e créditos da edição[cite: 11].

## Instalação Direta no Android (.APK)

1. Acesse a aba **[Releases](https://github.com/RomuloCSR/biblia-almeida-1911-android/releases)** na lateral direita desta página (ou abra a pasta `releases/BibliaAlmeida1911.apk` neste repositório) e baixe o arquivo **`BibliaAlmeida1911.apk`** no seu celular[cite: 11, 12].
2. Toque no arquivo baixado na barra de notificações ou na pasta *Downloads* do seu smartphone Android[cite: 11].
3. Caso o Android solicite permissão para instalar aplicativos fora da Play Store, toque em **Configurações**, ative **Permitir desta fonte** e confirme em **Instalar** (ou **Instalar assim mesmo**, caso o Google Play Protect exiba o aviso padrão de aplicativo independente).

## Este aplicativo é seguro? (Sobre alertas de segurança do sistema)

**Sim, 100% seguro.** Este é um projeto independente, gratuito e sem fins lucrativos, publicado em código aberto no **GitHub** (plataforma de referência mundial utilizada por desenvolvedores)[cite: 12].

* **Por que o Android exibe alerta ao instalar um arquivo `.apk`?** Sistemas operacionais modernos (Android, Windows, macOS e iOS) emitem avisos preventivos para qualquer aplicativo que não possua um certificado comercial pago nem esteja publicado nas lojas oficiais (Google Play, Microsoft Store ou App Store)[cite: 12].
* **Transparência total (Código Aberto):** Todo o código-fonte deste aplicativo (`motor.biblia.c`, `native-lib.cpp`, `MainActivity.kt`) e os textos dos 66 livros estão abertos e visíveis nesta página[cite: 11, 12]. Qualquer técnico ou programador pode inspecionar o código e confirmar que não há coleta de dados, rastreamento ou arquivos maliciosos[cite: 12].

## Estrutura do Projeto

* `app/src/main/assets/` — Base textual completa dos 66 livros em Markdown[cite: 11]
* `app/src/main/cpp/motor.biblia.c` — Núcleo portátil em C (tabelas, parser e ortografia)[cite: 11]
* `app/src/main/cpp/native-lib.cpp` — Ponte JNI entre C/AssetManager e Kotlin[cite: 11]
* `app/src/main/java/br/com/romulocsr/biblia1911/MainActivity.kt` — Interface Android e navegação[cite: 11]
* `releases/BibliaAlmeida1911.apk` — Pacote instalável pronto para distribuição[cite: 11]

## Autor, Colaboração e Licença

* **Autor:** Romulo CSR ([github.com/RomuloCSR](https://github.com/RomuloCSR)) — projeto de código aberto com o propósito de oferecer acesso livre, gratuito e fiel às Escrituras em dispositivos móveis[cite: 11, 12].
* **Apoio espontâneo via PIX:** `21980934118`[cite: 12]
