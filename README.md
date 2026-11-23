# Bíblia Almeida ARC-1911 (Edição 11/2026)

Aplicativo Android nativo, leve e **100% offline**, desenvolvido com motor de processamento e atualização ortográfica em **linguagem C pura** (`motor.biblia.c`) integrado via JNI a uma interface limpa em **Kotlin**.

## Destaques da Edição

* **Texto Base:** Almeida Revista e Corrigida (ARC-1911) com **atualização ortográfica e gramatical (Edição 11/2026)**.
* **100% Offline e Sem Anúncios:** Todos os 66 livros (Antigo e Novo Testamento) acompanham o aplicativo, sem depender de internet.
* **Motor Nativo em C (`motor.biblia.c`):** Leitura instantânea de capítulos, limpeza de marcações e atualização ortográfica executadas diretamente em código nativo compilado via Android NDK/CMake.
* **Leitura Confortável e Compartilhamento:** Controle rápido de tamanho de fonte (`A-` / `A+`), seleção de versículos e compartilhamento completo de capítulos com referência e créditos da edição.

## Instalação Direta no Android (.APK)

1. Baixe o arquivo `releases/BibliaAlmeida1911.apk` diretamente neste repositório.
2. Toque no arquivo baixado no seu smartphone Android e autorize a instalação.

## Estrutura do Projeto

* `app/src/main/assets/` — Base textual completa dos 66 livros em Markdown
* `app/src/main/cpp/motor.biblia.c` — Núcleo portátil em C (tabelas, parser e ortografia)
* `app/src/main/cpp/native-lib.cpp` — Ponte JNI entre C/AssetManager e Kotlin
* `app/src/main/java/br/com/romulocsr/biblia1911/MainActivity.kt` — Interface Android e navegação
* `releases/BibliaAlmeida1911.apk` — Pacote instalável pronto para distribuição

## Contribuições e Licença

Projeto de código aberto mantido por **@RomuloCSR** (`https://github.com/RomuloCSR`) com o propósito de oferecer acesso livre, gratuito e fiel às Escrituras em dispositivos móveis.

🤝 Apoie esta Obra
Autor: Romulo CSR (github.com/RomuloCSR)

Contribuição espontânea via PIX: 21980934118

Licença do texto bíblico: Domínio Público (Almeida Revista e Corrigida 1911).
