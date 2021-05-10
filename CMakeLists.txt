cmake_minimum_required(VERSION 3.19)
project(Argo)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Argo
        src/main.cpp
        src/main.h)
