cmake_minimum_required(VERSION 3.6)
project(Iturburu_kodea)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(Iturburu_kodea ${SOURCE_FILES})