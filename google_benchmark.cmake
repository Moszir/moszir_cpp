include(FetchContent)

# Google benchmark 1.9.1 (2024 November 28)
FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG c58e6d0710581e3a08d65c349664128a8d9a2461
        FIND_PACKAGE_ARGS NAMES benchmark
)
FetchContent_MakeAvailable(google_benchmark)

# Just link like this:
# target_link_libraries(target_name benchmark::benchmark)
