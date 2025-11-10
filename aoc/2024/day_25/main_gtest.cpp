/**
* @file main_gtest.cpp
 *
 * GTest for the solution for 2024 day 25.
 * This way we can test automatically that the solution is correct, and stays correct.
 */
#include "solver.hpp"
#include "gtest/gtest.h"

#define TEST_NAME AoC2024Day25

using namespace std::string_literals;

TEST(TEST_NAME, Part1Example)
{
    aoc::year2024::day25::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("3", solver.solvePart1());
}

TEST(TEST_NAME, Part1RealInput)
{
    aoc::year2024::day25::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("3107", solver.solvePart1());
}
