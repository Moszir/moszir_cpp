cmake_minimum_required(VERSION 3.18)
project(moszir)

set(CMAKE_CXX_STANDARD 23)

# The main library
add_subdirectory(lib)

# Projects that use the library
add_subdirectory(aoc_2024)

