cmake_minimum_required(VERSION 4.0)
project(cryptopi C)

set(CMAKE_C_STANDARD 11)

add_executable(cryptopi main.c
        lib/aes.h
        lib/aes.c)
