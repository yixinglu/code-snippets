cmake_minimum_required(VERSION 3.2)

project(DeleteComments)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -std=c++14")

add_executable(del-cpp-comments delete_comments.cc)
