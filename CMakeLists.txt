cmake_minimum_required(VERSION 3.6)
project(ex3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -Wall -Werror -Wvla -std=c99")


set(SOURCE_FILES GenericDFS.h GenericDFS.c SudokuSolver.c SudokuTree.c SudokuTree.h Stack.c Stack.h)

add_executable(ex3 ${SOURCE_FILES})

target_link_libraries(ex3 m)