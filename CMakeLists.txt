cmake_minimum_required(VERSION 3.15)
project(1715551 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/robot.h
        ${CMAKE_SOURCE_DIR}/robot.c
        ${CMAKE_SOURCE_DIR}/simulation.h
        ${CMAKE_SOURCE_DIR}/simulation.c
        ${CMAKE_SOURCE_DIR}/main.c
        )
add_executable(1715551 ${SOURCE_FILES})