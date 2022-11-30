cmake_minimum_required(VERSION 3.20)
project(multithreaded_matrix_multiplication_thread)

set(CMAKE_CXX_STANDARD 20)

add_executable(multithreaded_matrix_multiplication_thread main.cpp matrix.cpp matrix.h)
