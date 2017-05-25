cmake_minimum_required(VERSION 3.7)
project(BSSS17BauerZibler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bs/functions.cpp
        bs/functions.h
        bs/main.cpp)

add_executable(BSSS17BauerZibler ${SOURCE_FILES})