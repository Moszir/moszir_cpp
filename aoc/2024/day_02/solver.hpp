#pragma once

#include "aoc/aoc.hpp"
#include "moszir/ifstream.hpp"
#include "moszir/vector.hpp"

#include <iostream>
#include <ranges>

namespace aoc::year2024::day02
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        while (in)
        {
            auto& v = vectors_.emplace_back();
            while (!in.isEndOfLineNext())
            {
                in >> v;
            }
            in.ignoreEndOfLines();
        }
    }

    std::string solvePart1() override
    {
        return std::to_string(vectors_.count_if(isSafe));
    }

    std::string solvePart2() override
    {
        return std::to_string(vectors_.count_if([](const auto& v) { return isSafe(v) || canBeMadeSafe(v); }));
    }

private:

    using Vector = moszir::Vector<int32_t>;
    moszir::Vector<Vector> vectors_;

    /**
     * @brief Check if the given vector is safe.
     *
     * A vector is safe if it is either strictly increasing, or strictly decreasing,
     * and the difference of consecutive elements is no larger than 3.
     *
     * This is equivalent to checking that every difference of consecutive elements is between 1 and 3 (increasing case),
     * or they are all between -3 and -1 (decreasing case).
     *
     * @param v The vector to check.
     * @return true if the vector is safe, false otherwise.
     */
    static bool isSafe(const Vector& v)
    {
        return
            std::ranges::all_of(
                std::views::pairwise_transform(v, std::minus{}),
                [](const auto& diff) { return 0 < diff && diff <= 3; })
            || std::ranges::all_of(
                std::views::pairwise_transform(v, std::minus{}),
                [](const auto& diff) { return -3 <= diff && diff < 0; });
    }

    /**
     * @brief Check if the given vector can be made safe by removing one element.
     *
     * @param v The vector to check.
     * @return true if the vector can be made safe, false otherwise.
     */
    static bool canBeMadeSafe(const Vector& v)
    {
        return std::ranges::any_of(
            std::views::iota(0u, v.size()),
            [&v](const std::size_t i)
            {
                return isSafe(v.slice(0, i) + v.slice(i + 1));
            });
    }
};

} // namespace aoc::year2024::day02
