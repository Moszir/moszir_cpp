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
 * @param sw The string_view to parse.
 * @return The result of the multiplication, or -1 if the string_view does not start with a valid multiplication instruction.
 */
int64_t parseMul(const std::string_view& sw)
{
    if (sw.starts_with("mul("))
    {
        // Matching 1-3 digits, a comma, 1-3 digits, a closing parenthesis and then anything else.
        static const std::regex re(R"((\d{1,3}),(\d{1,3})\).*)");

        const std::string s(sw.substr(4, std::min(8ull, sw.size() - 4)));
        if (std::smatch match; std::regex_match(s, match, re))
        {
            return std::stoll(match[1]) * std::stoll(match[2]);
        }
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

        for (std::size_t i = 0; i < instructions.size(); ++i)
        {
            if (const auto mul = parseMul(instructions.substr(i)); mul != -1)
            {
                part1 += mul;
                if (on)
                {
                    part2 += mul;
                }
                i += 7; // skip "mul(1,1)", 7+1 characters, but the loop will increment i by 1 too.
            }
            else if (instructions.compare(i, std::strlen("do()"), "do()") == 0)
            {
                on = true;
                i += 3; // skip "do()", 3+1 characters, but the loop will increment i by 1 too.
            }
            else if (instructions.compare(i, std::strlen("don't()"), "don't()") == 0)
            {
                on = false;
                i += 6; // skip "don't()", 6+1 characters, but the loop will increment i by 1 too.
            }
        }
    }
    file.close();

    std::cout
        << "Part 1: " << part1 << '\n'       // 188'192'787
        << "Part 2: " << part2 << std::endl; // 113'965'544

    return 0;
}
