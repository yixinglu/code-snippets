
cmake_minimum_required(VERSION 2.8.3)

project(test-make)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_executable(test-make main.cc bar.cc foo.cc)
add_executable(test test.cc bar.cc foo.cc)
