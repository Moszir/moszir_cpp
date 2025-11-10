#pragma once

#include "aoc/aoc.hpp"

namespace aoc::year2024::day01
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        while (!in.eof())
        {
            in >> left >> right;
        }
        left.sort();
        right.sort();
    }

    std::string solvePart1() override
    {
        int64_t result = 0;
        for (size_t i = 0; i < left.size(); ++i)
        {
            result += std::abs(left[i] - right[i]);
        }
        return std::to_string(result);
    }

    std::string solvePart2() override
    {
        const auto rightCounts = right.countMap();

        size_t result = 0;
        for (const auto& [value, count] : left.countMap())
        {
            result += value * count * rightCounts.get(value, 0);
        }
        return std::to_string(result);
    }

private:

    moszir::Vector<int64_t> left;
    moszir::Vector<int64_t> right;
};

} // namespace aoc::year2024::day01
