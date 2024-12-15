#include "moszir/vector.hpp"

#include <iostream>
#include <unordered_map>


int main()
{
    // Parse input
    moszir::Vector<int64_t> left, right;

    std::ifstream file(__FILE__"/../input.txt");
    while (!file.eof())
    {
        file >> left >> right;
    }
    left.sort();
    right.sort();

    // Solve part 1
    int64_t part1 = 0;
    for (size_t i = 0; i < left.size(); ++i)
    {
        part1 += std::abs(left[i] - right[i]);
    }
    std::cout << "Part 1: " << part1 << '\n'; // 1'258'579

    // Solve part 2
    const auto leftCounts = left.countMap();
    const auto rightCounts = right.countMap();

    size_t part2 = 0;
    for (const auto& [value, count] : leftCounts)
    {
        part2 += value * count * rightCounts.get(value, 0);
    }
    std::cout << "Part 2: " << part2 << '\n'; // 23'981'443

    return 0;
}
