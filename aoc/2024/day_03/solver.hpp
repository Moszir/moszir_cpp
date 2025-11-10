#pragma once

#include "aoc/aoc.hpp"

#include <regex>

using namespace std::string_literals;


namespace aoc::year2024::day03
{

class Solver final : public aoc::Solver
{
public:

    void parse(moszir::Ifstream& in) override
    {
        instructions_ = in.readFile();
        instructions_.removeCharacter('\n');
    }

    std::string solvePart1() override
    {
        std::string_view view(instructions_);
        int64_t result = 0;

        while (!view.empty())
        {
            if (view.starts_with("mul("))
            {
                view.remove_prefix("mul("s.size());
                if (const auto mul = parseMul(view); mul != -1)
                {
                    result += mul;
                    view.remove_prefix("1,1)"s.size()); // we can skip at least this much
                }
            }
            else
            {
                view.remove_prefix(1);
            }
        }
        return std::to_string(result);
    }

    std::string solvePart2() override
    {
        std::string_view view(instructions_);
        bool on = true;
        int64_t result = 0;

        while (!view.empty())
        {
            if (on)
            {
                if (view.starts_with("mul("))
                {
                    view.remove_prefix("mul("s.size());
                    if (const auto mul = parseMul(view); mul != -1)
                    {
                        result += mul;
                        view.remove_prefix("1,1)"s.size()); // we can skip at least this much
                    }
                }
                else if (view.starts_with("don't()"))
                {
                    on = false;
                    view.remove_prefix("don't()"s.size());
                }
                else
                {
                    view.remove_prefix(1);
                }
            }
            else
            {
                if (view.starts_with("do()"))
                {
                    on = true;
                    view.remove_prefix("do()"s.size());
                }
                else
                {
                    view.remove_prefix(1);
                }
            }
        }
        return std::to_string(result);
    }

private:

    moszir::String instructions_;

    /**
     * @brief Parse the multiplication instruction at the beginning of the string_view.
     *
     * The instruction is expected to be in the form "mul(x,y)" where x and y are 1-3 digit numbers.
     * But we already chopped off the "mul(" part.
     *
     * @param sw The string_view to parse.
     * @return The result of the multiplication, or -1 if the string_view does not start with a valid multiplication instruction.
     */
    static int64_t parseMul(const std::string_view& sw)
    {
        static const std::regex re(R"((\d{1,3}),(\d{1,3})\).*)");

        const std::string s(sw.substr(0, std::min(static_cast<std::size_t>(8), sw.size())));
        if (std::smatch match; std::regex_match(s, match, re))
        {
            return std::stoll(match[1]) * std::stoll(match[2]);
        }
        return -1;
    }
};

} // namespace aoc::year2024::day03
