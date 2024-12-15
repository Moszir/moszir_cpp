# The library

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/moszir/*.hpp)
add_library(moszir INTERFACE)
target_sources(moszir INTERFACE ${HEADERS})
target_include_directories(moszir INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
