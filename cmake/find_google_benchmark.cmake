include(FetchContent)

# Google Benchmark 1.9.4
# 2025 May 19 (latest as of 2025 November 10)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.4
    FIND_PACKAGE_ARGS NAMES benchmark
)

FetchContent_MakeAvailable(google_benchmark)
