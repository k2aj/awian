cmake_minimum_required(VERSION 3.13)
project(awian)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(awian source/main.cpp)
target_compile_options(
    awian PRIVATE 
    -Wall -Wextra -Wshadow
    -Wno-unused-parameter   # this one is almost never helpful and usually just annoying
)