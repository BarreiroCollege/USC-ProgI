cmake_minimum_required(VERSION 3.15)
project(boletin5 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_library(bignum src/bignum/library.c src/bignum/utils.c src/bignum/math.c)
add_executable(main src/main.c src/rsa.c)