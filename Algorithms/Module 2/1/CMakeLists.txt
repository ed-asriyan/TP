cmake_minimum_required(VERSION 3.6)
project(Strings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -Wall -O2 -std=gnu++11 -lm")

set(SOURCE_FILES main.cpp)
add_executable(Strings ${SOURCE_FILES})