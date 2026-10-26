#MSoA - It would be possible to use std::filesystem instead but
# this library does not have the same behavior and provides
# different functions and classes (particularly, std::filesystem::resolver does not exist)
cmake_minimum_required(VERSION 3.5..4.0)
project(path)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # Enable C++11 mode on GCC / Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
add_executable(path_demo path_demo.cpp filesystem/path.h filesystem/resolver.h)
