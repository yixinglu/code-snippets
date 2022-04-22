add_executable(
  future
  future.cc
)

add_executable(
  thread
  thread.cpp
)

target_link_libraries(future pthread)
target_link_libraries(thread pthread)
