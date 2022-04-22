cmake_minimum_required(VERSION 3.1)

project("Code Snippets")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(lambda)
add_subdirectory(memory)
add_subdirectory(stl)
add_subdirectory(socket)
add_subdirectory(make)
add_subdirectory(mpl)
add_subdirectory(design-pattern)
add_subdirectory(cpp-basic)
add_subdirectory(thread)
add_subdirectory(time)
add_subdirectory(test)
add_subdirectory(template)
add_subdirectory(string)
add_subdirectory(performance)
