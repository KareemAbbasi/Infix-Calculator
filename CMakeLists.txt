cmake_minimum_required(VERSION 3.12)
project(ex3 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -Wvla -Wextra -lm")

add_executable(ex3 main.c stack.c)