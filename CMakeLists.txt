cmake_minimum_required(VERSION 3.12)
project(Matrix VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Computational-Math")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(Computational-Math)
#add_subdirectory(1_sem)
add_subdirectory(2_sem)