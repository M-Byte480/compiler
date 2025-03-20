cmake_minimum_required(VERSION 3.30)
project(untitled C)

set(CMAKE_C_STANDARD 17)

find_package(FLEX REQUIRED)

FLEX_TARGET(Lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/flexer.c)


add_executable(untitled main.c
        lexical.c
        lexical.h
        scanner.h
        scanner.c)
