
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(sock_test SHARED
  src/socket.cc
  src/server_socket.cc)

add_executable(server test/server.cc)
add_executable(client test/client.cc)

target_link_libraries(server sock_test)
target_link_libraries(client sock_test)
