#pragma once

#include "unordered_map.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <span>
#include <sstream>
#include <vector>

namespace moszir
{

// Forward declaration to break circular dependency
class String;

template <typename ValueType>
class Vector : public std::vector<ValueType>
{
    using BaseClass = std::vector<ValueType>;
    using SpanType = std::span<const ValueType>;

public:

    using BaseClass::BaseClass;

    #pragma region Comparison
    bool equals(const Vector& other) const
    {
        return BaseClass::size() == other.size() &&
            std::equal(BaseClass::begin(), BaseClass::end(), other.begin());
    }

    bool equals(SpanType other) const
    {
        return BaseClass::size() == other.size() &&
            std::equal(BaseClass::begin(), BaseClass::end(), other.begin());
    }
    #pragma endregion


    #pragma region Slicing

    /**
     * @brief Slices the vector.
     *
     * @param beginIndex The index of the first element to include.
     * @param endIndex The index after the last element to include.
     *
     * @return The sliced vector.
     *
     * @note Negative indices are counted from the end of the vector.
     * @note If `beginIndex` is greater than or equal to `endIndex`, an empty vector is returned.
     */
    [[nodiscard]]
    Vector slice(const int64_t beginIndex, const int64_t endIndex) const
    {
        return slice(indexify(beginIndex), indexify(endIndex));
    }

    /**
     * @brief Slices the vector.
     *
     * @param[in] beginIndex The index of the first element to include.
     * @param[in] endIndex The index after the last element to include.
     * @return The sliced vector.
     *
     * @note If `beginIndex` is greater than or equal to `endIndex`, an empty vector is returned.
     */
    [[nodiscard]]
    Vector slice(const size_t beginIndex, const size_t endIndex) const
    {
        if (beginIndex >= endIndex)
        {
            return {};
        }

        Vector result;
        result.reserve(endIndex - beginIndex);
        std::copy(
            BaseClass::begin() + beginIndex,
            BaseClass::begin() + endIndex,
            std::back_inserter(result));
        return result;
    }

    [[nodiscard]]
    Vector slice(const int64_t beginIndex) const
    {
        return slice(beginIndex, static_cast<int64_t>(BaseClass::size()));
    }

    [[nodiscard]]
    Vector slice(const size_t beginIndex) const
    {
        return slice(beginIndex, BaseClass::size());
    }

    [[nodiscard]]
    SpanType slice_view(const int64_t beginIndex, const int64_t endIndex) const
    {
        const auto beginIndex_ = indexify(beginIndex);
        const auto endIndex_ = indexify(endIndex);
        return beginIndex_ < endIndex_
            ? SpanType{BaseClass::begin() + beginIndex_, endIndex_ - beginIndex_}
            : SpanType{};
    }

    [[nodiscard]]
    SpanType slice_view(const int64_t beginIndex) const
    {
        return slice_view(beginIndex, BaseClass::size());
    }

    /**
     * @brief Concatenates two vectors.
     *
     * @param other The other vector.
     *
     * @return The concatenated vector.
     */
    [[nodiscard]]
    Vector operator+(const Vector& other) const
    {
        Vector result;
        result.reserve(BaseClass::size() + other.size());
        std::copy(BaseClass::begin(), BaseClass::end(), std::back_inserter(result));
        std::copy(other.begin(), other.end(), std::back_inserter(result));
        return result;
    }
    #pragma endregion


    #pragma region Algorithms

    bool all_of(auto&& predicate) const
    {
        return std::ranges::all_of(BaseClass::begin(), BaseClass::end(), predicate);
    }

    auto count_if(auto&& predicate) const
    {
        return std::ranges::count_if(BaseClass::begin(), BaseClass::end(), predicate);
    }

    template<typename ReturnType>
    ReturnType transformReduce(
        std::function<ReturnType(const ValueType&)> transform,
        std::function<ReturnType(ReturnType, ReturnType)> reduce = std::plus<ReturnType>{},
        ReturnType initialValue = ReturnType{}) const
    {
        ReturnType result = initialValue;
        for (const auto& value : *this)
        {
            result = reduce(result, transform(value));
        }
        return result;
    }

    Vector& sort()
    {
        std::ranges::sort(
            BaseClass::begin(),
            BaseClass::end());
        return *this;
    }
    #pragma endregion


    #pragma region Output

    std::ostream& print(const std::string& separator = ", ", std::ostream& out = std::cout) const
    {
        for (auto it = BaseClass::begin(); it != BaseClass::end();)
        {
            out << *it;
            if (++it != BaseClass::end())
            {
                out << separator;
            }
        }
        return out;
    }

    std::ostream& print(const char separator = ',', std::ostream& out = std::cout) const
    {
        return print(std::string(1, separator), out);
    }
    #pragma endregion


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

private:

    /**
     * @brief Converts a potentially negative index to a non-negative index.
     * @param index The potentially negative index.
     * @return The non-negative index.
     *
     * For example: <c>indexify(-1)</c> returns <c>size() - 1</c>.
     */
    [[nodiscard]]
    size_t indexify(int64_t index) const
    {
        if (index < 0)
        {
            index %= BaseClass::size();
            if (index < 0) index += BaseClass::size();
        }
        return index;
    }
};

/**
 * @brief Reads an element from the input stream and appends it to the vector.
 * @tparam ValueType The type of the elements in the vector.
 * @param inStream The input stream.
 * @param v The vector.
 * @return The input stream.
 */
template <typename ValueType>
std::istream& operator>> (std::istream& inStream, Vector<ValueType>& v)
{
    ValueType value;
    inStream >> value;
    v.push_back(value);
    return inStream;
}

/**
 * @brief Writes the vector to the output stream.
 * @tparam ValueType The type of the elements in the vector.
 * @param out The output stream.
 * @param v The vector.
 * @return The output stream (so that you can chain calls).
 */
template <typename ValueType>
std::ostream& operator<< (std::ostream& out, const Vector<ValueType>& v)
{
    v.print(", ", out);
    return out;
}

} // namespace moszir
