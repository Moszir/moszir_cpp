#pragma once

#include "aoc/aoc.hpp"

#include <array>
#include <numeric>

#include "moszir/vector.hpp"

namespace aoc::year2024::day25
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        while (in)
        {
            std::string topLine;
            std::array<std::string, 5> lines;
            std::string bottomLine;
            in >> topLine >> lines[0] >> lines[1] >> lines[2] >> lines[3] >> lines[4] >> bottomLine;
            if (bottomLine.empty())
            {
                // EOF
                break;
            }

            Pattern pattern{};
            for (const auto& line: lines)
            {
                for (size_t i = 0; i < 5; ++i)
                {
                    pattern[i] += line[i] == '#' ? 1 : 0;
                }
            }
            (topLine[0] == '#' ? keys : locks).push_back(pattern);
        }
    }

    std::string solvePart1() override
    {
        return std::to_string(
            keys.transformReduce<size_t>(
                [this](const Pattern& key)
                {
                    return locks.count_if([&key](const Pattern& lock) { return match(key, lock); });
                }));
    }

    // Day 25 has no part 2
    std::string solvePart2() override
    {
        return {};
    }

private:

    using Pattern = std::array<uint32_t, 5u>;
    moszir::Vector<Pattern> keys;
    moszir::Vector<Pattern> locks;

    static bool match(const Pattern& key, const Pattern& lock)
    {
        for (size_t i = 0; i < 5; ++i)
        {
            if (key[i] + lock[i] > 5)
            {
                return false;
            }
        }
        return true;
    }
};

} // namespace aoc::year2024::day25
