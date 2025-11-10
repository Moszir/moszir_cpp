#include "solver.hpp"
#include "gtest/gtest.h"

#define TEST_NAME AoC2024Day04
using Solver = aoc::year2024::day04::Solver;

using namespace std::string_literals;

TEST(TEST_NAME, Part1Example)
{
    Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("18", solver.solvePart1());
}

TEST(TEST_NAME, Part1RealInput)
{
    Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("2571", solver.solvePart1());
}

TEST(TEST_NAME, Part2Example)
{
    Solver solver;
    solver.parseFile("example.txt"s);
    EXPECT_EQ("9", solver.solvePart2());
}

TEST(TEST_NAME, Part2RealInput)
{
    Solver solver;
    solver.parseFile("input.txt"s);
    EXPECT_EQ("1992", solver.solvePart2());
}
