# Common AoC library
add_library(aoc INTERFACE)
file(GLOB_RECURSE aoc_headers ${CMAKE_CURRENT_SOURCE_DIR}/common/aoc/*.hpp)
target_sources(aoc INTERFACE ${aoc_headers})
target_include_directories(aoc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(aoc INTERFACE moszir)
