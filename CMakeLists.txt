cmake_minimum_required(VERSION 3.16)
project(sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(sudoku main.c cmake-build-debug/test.c)