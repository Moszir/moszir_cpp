/**
 * @file day_03.cpp
 * @brief Solution for Advent of Code 2024 day 3.
 *
 * Link: https://adventofcode.com/2024/day/3
 */

#include <fstream>
#include <iostream>
#include <regex>


/**
 * @brief Parse the multiplication instruction at the beginning of the string_view.
 *
 * The instruction is expected to be in the form "mul(x,y)" where x and y are 1-3 digit numbers.
 * But we already chopped off the "mul(" part.
 *
 * @param sw The string_view to parse.
 * @return The result of the multiplication, or -1 if the string_view does not start with a valid multiplication instruction.
 */
int64_t parseMul(const std::string_view& sw)
{
    static const std::regex re(R"((\d{1,3}),(\d{1,3})\).*)");

    const std::string s(sw.substr(0, std::min(8ull, sw.size())));
    if (std::smatch match; std::regex_match(s, match, re))
    {
        return std::stoll(match[1]) * std::stoll(match[2]);
    }
    return -1;
}

int main()
{
    std::ifstream file(__FILE__ "/../input.txt");
    std::string instructions;

    int64_t part1 = 0ull;
    int64_t part2 = 0ull;
    bool on = true;

    while (!file.eof())
    {
        // Using that a whitespace character would interrupt all 3 instructions
        instructions.clear();
        file >> instructions;

        std::string_view view(instructions);

        while (!view.empty())
        {
            if (view.starts_with("mul("))
            {
                view.remove_prefix(std::strlen("mul("));
                if (const auto mul = parseMul(view); mul != -1)
                {
                    part1 += mul;
                    if (on)
                    {
                        part2 += mul;
                    }
                    view.remove_prefix(4); // skip at least "1,1)": 4 characters
                }
            }
            else if (view.starts_with("do()"))
            {
                on = true;
                view.remove_prefix(std::strlen("do()"));
            }
            else if (view.starts_with("don't()"))
            {
                on = false;
                view.remove_prefix(std::strlen("don't()"));
            }
            else
            {
                view.remove_prefix(1);
            }
        }
    }
    file.close();

    std::cout
        << "Part 1: " << part1 << '\n'       // 188'192'787
        << "Part 2: " << part2 << std::endl; // 113'965'544

    return 0;
}
