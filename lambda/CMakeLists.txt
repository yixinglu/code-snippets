
cmake_minimum_required(VERSION 2.8.3)

project(lambda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_executable(lambda main.cpp)
