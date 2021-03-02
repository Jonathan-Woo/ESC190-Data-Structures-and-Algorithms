cmake_minimum_required(VERSION 3.17)
project(Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project
        autocomplete.c
        autocomplete.h
        main.c)
