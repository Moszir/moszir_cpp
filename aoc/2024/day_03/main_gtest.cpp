/**
 * @file main_gtest.cpp
 *
 * GTest for the solution for 2024 day 3.
 * This way we can test automatically that the solution is correct, and stays correct.
 */
#include "solver.hpp"
#include "gtest/gtest.h"

using namespace std::string_literals;

TEST(AoC2024Day03, Part1Example)
{
    aoc::year2024::day03::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("161", solver.solvePart1());
}

TEST(AoC2024Day03, Part2Example)
{
    aoc::year2024::day03::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("48", solver.solvePart2());
}

TEST(AoC2024Day03, Part1RealInput)
{
    aoc::year2024::day03::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("188192787", solver.solvePart1());
}

TEST(AoC2024Day03, Part2RealInput)
{
    aoc::year2024::day03::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("113965544", solver.solvePart2());
}
