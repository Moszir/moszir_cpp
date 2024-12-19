#include "moszir/vector.hpp"

#include "benchmark/benchmark.h"

static std::vector<int> protoV{};
static void generatePrototype()
{
    if (protoV.empty())
    {
        for (int i = 0; i < 1'000'000; ++i)
        {
            // Yes, this is not "random" enough, but that's not the point of this benchmark.
            protoV.push_back(rand()); // NOLINT(*-msc50-cpp)
        }
    }
}

static void benchmarkVectorSort(benchmark::State& state)
{
    generatePrototype();
    moszir::Vector<int> v{};
    std::ranges::copy(protoV, std::back_inserter(v));

    for ([[maybe_unused]] auto _ : state)
    {
        v.sort();
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkVectorSort);


static void benchmarkStdVectorSort(benchmark::State& state)
{
    generatePrototype();
    std::vector<int> v{};
    std::ranges::copy(protoV, std::back_inserter(v));

    for ([[maybe_unused]] auto _ : state)
    {
        std::sort(v.begin(), v.end());
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkStdVectorSort);

static void benchmarkStdRangesSort(benchmark::State& state)
{
    generatePrototype();
    std::vector<int> v{};
    std::ranges::copy(protoV, std::back_inserter(v));

    for ([[maybe_unused]] auto _ : state)
    {
        std::ranges::sort(v);
        benchmark::DoNotOptimize(v);
    }
}
BENCHMARK(benchmarkStdRangesSort);

BENCHMARK_MAIN();
