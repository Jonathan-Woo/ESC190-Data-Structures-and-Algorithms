cmake_minimum_required(VERSION 3.17)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project_2
        c_img.c
        c_img.h
        seamcarving.h
        seamcarving_draft.c)
