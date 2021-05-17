cmake_minimum_required(VERSION 3.17)
project(RTTI)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTTI main.cpp)
add_compile_options(-fno-rtti)