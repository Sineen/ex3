cmake_minimum_required(VERSION 3.6)
project(ex3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -Wall -Werror -Wvla")

set(SOURCE_FILES
    GenericDFS.h)

add_executable(ex3 ${SOURCE_FILES})