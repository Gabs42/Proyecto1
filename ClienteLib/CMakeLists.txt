cmake_minimum_required(VERSION 3.8)
project(ClienteLib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h)
add_library(ClienteLib SHARED ${SOURCE_FILES})