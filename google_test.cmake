include(FetchContent)

# Google test 1.15.2 (2024 July 31)
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

# Link like this:
# target_link_libraries(target_name gtest gtest_main)

# Then you can use gtest_discover_tests, and can add optional labels:
# gtest_discover_tests(target_name [PROPERTIES LABELS label])
