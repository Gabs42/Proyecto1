cmake_minimum_required(VERSION 3.8)
project(cliente)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)
add_library(cliente STATIC ${SOURCE_FILES})