cmake_minimum_required(VERSION 3.27)
project(Listes C)

set(CMAKE_C_STANDARD 99)

add_executable(Listes main.c
        testliste.c
        testliste.h)
