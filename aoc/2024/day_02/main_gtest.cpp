/**
 * @file main_gtest.cpp
 *
 * GTest for the solution for 2024 day 2.
 * This way we can test automatically that the solution is correct, and stays correct.
 */
#include "solver.hpp"
#include "gtest/gtest.h"

using namespace std::string_literals;

TEST(AoC2024Day02, Part1Example)
{
    aoc::year2024::day02::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("2", solver.solvePart1());
}

TEST(AoC2024Day02, Part2Example)
{
    aoc::year2024::day02::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("4", solver.solvePart2());
}

TEST(AoC2024Day02, Part1RealInput)
{
    aoc::year2024::day02::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("442", solver.solvePart1());
}

TEST(AoC2024Day02, Part2RealInput)
{
    aoc::year2024::day02::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("493", solver.solvePart2());
}
