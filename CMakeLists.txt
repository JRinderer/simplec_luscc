cmake_minimum_required(VERSION 3.30)
project(luscc C)

set(CMAKE_C_STANDARD 11)

add_executable(luscc main.c
        scanner.c
        scanner.h
        vars.h
        token.h)
