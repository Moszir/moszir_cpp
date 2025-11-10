# Function: add_aoc_executable
# ----------------------------
# Adds an executable target for an Advent of Code (AoC) day and year,
# and copies necessary input files to the build directory.
#
# Parameters:
#   year - The year of the AoC challenge (e.g., 2024).
#   day  - The day of the AoC challenge (e.g., 01).
#
# The function performs the following steps:
# 1. Creates an executable target named "aoc_<year>_<day>" using the source file "main.cpp".
# 2. Links the target with the `moszir` and `aoc` libraries.
# 3. Copies the `input.txt` file from the source directory to the build directory if it exists.
# 4. Copies the `example.txt` file from the source directory to the build directory if it exists.
# 5. Copies any file with the `.in` extension from the source directory to the build directory.
#
# Example usage:
#   add_aoc_executable(2024 01)
#
# This will create an executable target named "aoc_2024_01" and copy the necessary input files if they exist.
function(add_aoc_executable year day)
    set(target_name "aoc_${year}_${day}")
    add_executable("${target_name}" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    target_link_libraries("${target_name}" PRIVATE moszir aoc)

    # copy the input.txt if it exists
    set(input_file "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    if(EXISTS "${input_file}")
        configure_file("${input_file}" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
    endif()

    # copy the example.txt if it exists
    set(example_file "${CMAKE_CURRENT_SOURCE_DIR}/example.txt")
    if(EXISTS "${example_file}")
        configure_file("${example_file}" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
    endif()

    # copy any file with the extension `.in` too
    file(GLOB in_files "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
    foreach(in_file ${in_files})
        get_filename_component(file_name ${in_file} NAME)
        configure_file("${in_file}" "${CMAKE_CURRENT_BINARY_DIR}/${file_name}" COPYONLY)
    endforeach()
endfunction()
