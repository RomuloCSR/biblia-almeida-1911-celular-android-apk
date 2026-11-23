cmake_minimum_required(VERSION 3.22.1)

project("biblia1911")

add_compile_definitions(__ANDROID_APP__)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        motor.biblia.c)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)
