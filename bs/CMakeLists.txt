cmake_minimum_required(VERSION 3.7)
project(bs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp functions.h)
add_executable(bs ${SOURCE_FILES})