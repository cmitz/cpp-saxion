cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(untitled main.cpp io.h io.cpp)