#pragma once

#include "unordered_map.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

namespace moszir
{

template <typename ValueType>
class Vector : public std::vector<ValueType>
{
    using BaseClass = std::vector<ValueType>;
    using This = Vector<ValueType>;

public:

    This& sort()
    {
        std::ranges::sort(
            BaseClass::begin(),
            BaseClass::end());
        return *this;
    }

    [[nodiscard]]
    UnorderedMap<ValueType, std::size_t> countMap() const
    {
        UnorderedMap<ValueType, std::size_t> counts;
        for (const auto value : *this)
        {
            ++counts[value];
        }
        return counts;
    }

};

inline std::ifstream& operator>> (std::ifstream& file, Vector<int64_t>& v)
{
    int64_t value;
    file >> value;
    v.push_back(value);
    return file;
}

} // namespace moszir
