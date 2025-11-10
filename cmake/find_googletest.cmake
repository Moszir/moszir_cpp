include(FetchContent)

# Google test 1.15.2 (2024 July 31)
# Latest as of 2024 September 19
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc898e2951020cbdca1304b75f5950d1f59
    FIND_PACKAGE_ARGS NAMES GTest
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

include(GoogleTest)

function(moszir_add_test test_name source_files)
    add_executable("${test_name}" "${source_files}")
    target_link_libraries("${test_name}" gtest gtest_main)
    # Add a custom label to the test so we can run all tests with `ctest -L moszir`
    # Otherwise the tests of the benchmark module would be run as well
    gtest_discover_tests("${test_name}" PROPERTIES LABELS "moszir")
endfunction()
