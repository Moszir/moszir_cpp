/**
 * @file main_gtest.cpp
 *
 * GTest for the solution for 2024 day 1.
 * This way we can test automatically that the solution is correct, and stays correct.
 */
#include "solver.hpp"
#include "gtest/gtest.h"

using namespace std::string_literals;

TEST(AoC2024Day01, Part1Example)
{
    aoc::year2024::day01::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("11", solver.solvePart1());
}

TEST(AoC2024Day01, Part2Example)
{
    aoc::year2024::day01::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("31", solver.solvePart2());
}

TEST(AoC2024Day01, Part1RealInput)
{
    aoc::year2024::day01::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("1258579", solver.solvePart1());
}

TEST(AoC2024Day01, Part2RealInput)
{
    aoc::year2024::day01::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("23981443", solver.solvePart2());
}
