function(add_day number)
    add_executable(aoc_2024_${number} day_${ARGV0}/day_${number}.cpp)
    target_link_libraries(aoc_2024_${number} PRIVATE moszir)
endfunction()

add_day(01)
add_day(02)
add_day(03)
