#include "moszir/ifstream.hpp"
#include "moszir/vector.hpp"

#include <iostream>
#include <ranges>


using Vector = moszir::Vector<int32_t>;

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
bool isSafe(const Vector& v)
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
bool canBeMadeSafe(const Vector& v)
{
    return std::ranges::any_of(
        std::views::iota(0u, v.size()),
        [&v](const std::size_t i) { return isSafe(v.slice(0, i) + v.slice(i + 1, v.size())); });
}

int main()
{
    Vector v;
    int safe = 0;
    int couldBeSafe = 0;

    moszir::Ifstream file(__FILE__ "/../input.txt");
    while (file)
    {
        v.clear();
        while (!file.isEndOfLineNext())
        {
            file >> v;
        }

        if (isSafe(v))
        {
            ++safe;
        }
        else if (canBeMadeSafe(v))
        {
            ++couldBeSafe;
        }

        file.ignoreEndOfLines();
    }

    std::cout << "Part 1: " << safe << std::endl; // 442
    std::cout << "Part 2: " << safe + couldBeSafe << std::endl; // 493

    return 0;
}
