cmake_minimum_required(VERSION 3.17)
project(Project_F C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project_F
        autocomplete.c
        autocomplete.h
        main.c)
