#include "moszir/vector.hpp"

#include "benchmark/benchmark.h"

/**
 * Generate a vector with one million random integers.
 * This same vector is used for all benchmarks to ensure that the only difference is the sorting algorithm.
 *
 * @tparam VectorType The type of the vector to create.
 * @return A vector with a million random integers.
 */
template<typename VectorType>
static VectorType getSortingPrototype()
{
    static std::vector<int> prototype{};
    if (prototype.empty())
    {
        for (int i = 0; i < 1'000'000; ++i)
        {
            // Yes, this is not "random" enough, but that's not the point of this benchmark.
            prototype.push_back(rand()); // NOLINT(*-msc50-cpp)
        }
    }

    VectorType result{};
    std::ranges::copy(prototype, std::back_inserter(result));
    return result;
}

/**
 * Benchmark `moszir::Vector::sort`.
 * @param state The benchmark state.
 */
static void benchmarkVectorSort(benchmark::State& state)
{
    auto v = getSortingPrototype<moszir::Vector<int>>();
    for ([[maybe_unused]] auto _ : state)
    {
        v.sort();
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkVectorSort);


/**
 * Benchmark `std::sort` used on an `std::vector`.
 * @param state The benchmark state.
 */
static void benchmarkVectorSortStd(benchmark::State& state)
{
    auto v = getSortingPrototype<std::vector<int>>();
    for ([[maybe_unused]] auto _ : state)
    {
        // The point of this benchmark is to use std::sort, not std::ranges::sort.
        // ReSharper disable once CppUseRangeAlgorithm
        std::sort(v.begin(), v.end());
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkVectorSortStd);

/**
 * Benchmark `std::ranges::sort` used on an `std::vector`.
 * @param state The benchmark state.
 */
static void benchmarkVectorSortRanges(benchmark::State& state)
{
    auto v = getSortingPrototype<std::vector<int>>();
    for ([[maybe_unused]] auto _ : state)
    {
        std::ranges::sort(v);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkVectorSortRanges);


/**
 * The benchmark results are roughly the same for all three cases.
 * It changes from run to run, which one is the fastest by a small margin.
 * This is the expected result.
 */
BENCHMARK_MAIN();
