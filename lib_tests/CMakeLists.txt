function(add_moszir_gtest module submodule)
    set(target moszir_${module}_${submodule}_tests)
    add_executable("${target}" "${submodule}.cpp")
    target_link_libraries("${target}" PRIVATE moszir gtest gtest_main)
    gtest_discover_tests("${target}" PROPERTIES LABELS moszir)
endfunction()

add_subdirectory(vector)
