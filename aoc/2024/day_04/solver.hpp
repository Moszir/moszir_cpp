#pragma once

#include "aoc/aoc.hpp"
#include "moszir/string_table.hpp"


namespace aoc::year2024::day04
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        dataTable_ = moszir::StringTable(in);
    }

    std::string solvePart1() override
    {
        int result = 0;
        dataTable_.findWords("XMAS", [&result](size_t, size_t) { ++result; });
        return std::to_string(result);
    }

    static bool isXmas(const char c1, const char c2, const char c3, const char c4)
    {
        return (c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S')
            || (c1 == 'S' && c2 == 'A' && c3 == 'M' && c4 == 'X');
    }

    std::string solvePart2() override
    {
        int result = 0;
        for (size_t row = 0; row + 2 < dataTable_.rowSize(); ++row)
        {
            for (size_t col = 0; col + 2 < dataTable_.columnSize(); ++col)
            {
                if (isMasCross(
                        dataTable_[row][col], dataTable_[row][col + 2],
                        dataTable_[row + 1][col + 1],
                        dataTable_[row + 2][col], dataTable_[row + 2][col + 2]))
                {
                    ++result;
                }
            }
        }
        return std::to_string(result);
    }

    static bool isMasCross(const char c1, const char c2, const char c3, const char c4, const char c5)
    {
        return c3 == 'A'
            && ((c1 == 'M' && c2 == 'M' && c4 == 'S' && c5 == 'S')
            || (c1 == 'S' && c2 == 'M' && c4 == 'S' && c5 == 'M')
            || (c1 == 'S' && c2 == 'S' && c4 == 'M' && c5 == 'M')
            || (c1 == 'M' && c2 == 'S' && c4 == 'M' && c5 == 'S')
    );
}

private:

    moszir::StringTable dataTable_;
};

} // namespace aoc::year2024::day04
