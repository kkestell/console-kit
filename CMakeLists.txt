cmake_minimum_required(VERSION 3.30)
project(console_kit C)

set(CMAKE_C_STANDARD 11)

add_executable(console_kit main.c
        event.c
        event.h
        mouse.c
        mouse.h
        keyboard.c
        keyboard.h)
