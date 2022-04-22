cmake_minimum_required(VERSION 2.8.3)

project("Code Snippets")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(lambda)
add_subdirectory(memory)
add_subdirectory(stl)
add_subdirectory(socket)
add_subdirectory(make)
