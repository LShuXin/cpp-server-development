cmake_minimum_required(VERSION 3.17)
project(c11_threadPool01)

set(CMAKE_CXX_STANDARD 11)
set(SRC_LIST
        main.cpp
        TaskPool.cpp)

add_executable(test ${SRC_LIST})