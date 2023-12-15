cmake_minimum_required(VERSION 3.17)
project(c11_threadPool02)

set(CMAKE_CXX_STANDARD 14)

add_executable(c11_threadPool02 main.cpp ThreadPool.cpp)