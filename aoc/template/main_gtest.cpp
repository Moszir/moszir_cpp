#include "solver.hpp"
#include "gtest/gtest.h"

#define TEST_NAME AoC2024Day25
using Solver = aoc::year2024::day25::Solver;

using namespace std::string_literals;

TEST(TEST_NAME, Part1Example)
{
    Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("3", solver.solvePart1());
}

TEST(AoC2024Day25, Part1RealInput)
{
    Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("3107", solver.solvePart1());
}

TEST(AoC2024Day25, Part2Example)
{
    Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("3", solver.solvePart2());
}

TEST(AoC2024Day25, Part2RealInput)
{
    Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("3107", solver.solvePart2());
}
