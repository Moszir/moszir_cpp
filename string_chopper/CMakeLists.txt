moszir_add_test(string_chopper string_chopper_tests.cpp)

function(moszir_add_benchmark name)
    add_executable(${name} "${name}.cpp")
    target_link_libraries(${name} benchmark::benchmark)
endfunction()

moszir_add_benchmark(string_chopper_benchmarks)
