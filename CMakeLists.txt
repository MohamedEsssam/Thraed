cmake_minimum_required(VERSION 3.12)

project(untitled1 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled1 main.c methode.c)

SET(CMAKE_CXX_FLAGS -pthread)

target_link_libraries(${PROJECT_NAME} pthread)