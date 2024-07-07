cmake_minimum_required(VERSION 3.10)
project(MatrixOperations)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

file(GLOB SOURCES "src/*.c")

add_executable(MatrixOperations main.c ${SOURCES})

target_include_directories(MatrixOperations PRIVATE inc)
