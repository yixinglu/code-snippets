
cmake_minimum_required (VERSION 2.6)

project(sock_test)

include_directories("${PROJECT_SOURCE_DIR}/src")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_library(sock_test SHARED
  src/socket.cc
  src/server_socket.cc)

add_executable(server test/server.cc)
add_executable(client test/client.cc)

target_link_libraries(server sock_test)
target_link_libraries(client sock_test)
