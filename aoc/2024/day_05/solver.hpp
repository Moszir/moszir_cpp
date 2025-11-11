#pragma once

#include "aoc/aoc.hpp"
#include "moszir/vector.hpp"

#include <sstream>
#include <algorithm>

namespace aoc::year2024::day05
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        while (in.good() && !in.isEndOfLineNext())
        {
            in >> rules_;
            in.ignoreEndOfLine(); // Ignore 1 line ending. If there are two, we go to reading updates.
        }

        while (in)
        {
            auto update = in.readVector<int>(",");
            if (update.empty()) break;
            updates_.push_back(std::move(update));
        }
    }

    std::string solvePart1() override
    {
        int part1 = 0;
        for (const auto& update : updates_)
        {
            const auto sorted_update = getSortedUpdate(update);
            if (update == sorted_update)
            {
                part1 += update[update.size() / 2];
            }
        }
        return std::to_string(part1);
    }

    std::string solvePart2() override
    {
        int part2 = 0;
        for (const auto& update : updates_)
        {
            const auto sorted_update = getSortedUpdate(update);
            if (update != sorted_update)
            {
                part2 += sorted_update[sorted_update.size() / 2];
            }
        }
        return std::to_string(part2);
    }

private:

    struct Rule
    {
        int before;
        int after;

        auto operator<=>(const Rule&) const = default;

        friend std::istream& operator>>(std::istream& in, Rule& rule)
        {
            char pipe = 0;
            return in >> rule.before >> pipe >> rule.after;
        }
    };

    auto getSortedUpdate(const moszir::Vector<int>& update) const -> moszir::Vector<int>
    {
        return update.createSorted([this](int u, int v){ return rules_.contains(Rule{u, v}); });
    }

    moszir::Vector<Rule> rules_;
    moszir::Vector<moszir::Vector<int>> updates_;
};

} // namespace aoc::year2024::day05
