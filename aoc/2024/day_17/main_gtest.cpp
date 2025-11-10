/**
* @file main_gtest.cpp
 *
 * GTest for the solution for 2024 day 17.
 * This way we can test automatically that the solution is correct, and stays correct.
 */
#include "solver.hpp"
#include "gtest/gtest.h"

using namespace std::string_literals;

TEST(AoC2024Day17, Part1Example)
{
    aoc::year2024::day17::Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("4,6,3,5,6,3,5,2,1,0", solver.solvePart1());
}

TEST(AoC2024Day17, Part2Example)
{
    aoc::year2024::day17::Solver solver;
    solver.parseFile("part2_example.in"s);
    EXPECT_EQ("117440", solver.solvePart2());
}

TEST(AoC2024Day17, Part1RealInput)
{
    aoc::year2024::day17::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("2,1,0,1,7,2,5,0,3", solver.solvePart1());
}

TEST(AoC2024Day17, Part2RealInput)
{
    aoc::year2024::day17::Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("267265166222235", solver.solvePart2());
}
