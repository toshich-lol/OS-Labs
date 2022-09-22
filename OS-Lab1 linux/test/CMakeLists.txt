cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp)

add_library(Project_number STATIC IMPORTED)
set_target_properties(Project_number PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../Number)
set_target_properties(Project_number PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../Number/cmake-build-debug/libProject_number.a)
target_link_libraries(test Project_number)

add_library(Vector SHARED IMPORTED)

set_target_properties(Vector PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../Vector)
set_target_properties(Vector PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../Vector/cmake-build-debug/libVector.so)
target_link_libraries(test Vector)