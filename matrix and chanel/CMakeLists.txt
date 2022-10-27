cmake_minimum_required(VERSION 3.20)
project(matrix_buff_channel)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix_buff_channel main.cpp buffered_channel.cpp buffered_channel.h matrix.cpp matrix.h)

add_compile_options(CMAKE_CXX_FLAGS "-O3")
