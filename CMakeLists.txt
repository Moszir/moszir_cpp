cmake_minimum_required(VERSION 3.18)
project(
    moszir
    LANGUAGES CXX
    VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

# 3rd party libraries
include(${CMAKE_CURRENT_SOURCE_DIR}/google_test.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/google_benchmark.cmake)

# The main library
add_subdirectory(lib)
add_subdirectory(lib_tests)
add_subdirectory(lib_benchmarks)

# Projects that use the library
add_subdirectory(aoc)
