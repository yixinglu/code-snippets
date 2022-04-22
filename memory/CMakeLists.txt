
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_executable(
    atomic_pointer
    atomic_pointer.cpp
  )
endif()

add_executable(
  mutual_ref
  mutual_ref.cpp
)

add_executable(
  shared_ptr
  shared_ptr.cc
)

add_executable(
  scope_guard
  scope_guard.cpp
)
