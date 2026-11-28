# =============================================================================
# CMakeLists.txt — biblioteca nativa do app Android (libbiblia1911.so)
#
# O que faz: compila a ponte JNI (native-lib.cpp) junto com o kernel da Bíblia.
# Por quê:   desde 28/11/2026 o texto vem do kernel (pasta kernel/), o mesmo
#            resultado do motor.biblia.c, cerca de 12 vezes mais rápido.
# Fonte:     kernel/LEIAME.md
# =============================================================================
cmake_minimum_required(VERSION 3.22.1)

project("biblia1911")

add_compile_definitions(__ANDROID_APP__)

# 1. Arquivos: ponte JNI + kernel (as tabelas de kernel/gerado/ entram pelo #include)
add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        kernel/biblia_kernel.c)

# 2. O kernel é C99
set_source_files_properties(kernel/biblia_kernel.c PROPERTIES COMPILE_OPTIONS "-std=c99")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/kernel)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)
