#pragma once

#include "vector.hpp"

#include <algorithm>
#include <string>


namespace moszir
{

/**
 * @brief An <c>std::string</c> with additional functionality.
 */
class String : public std::string
{
    using BaseClass = std::string;

public:

    using BaseClass::BaseClass;

    explicit String(std::string&& s) : BaseClass(std::move(s)) {}

    void removeCharacter(char c)
    {
        erase(std::remove(BaseClass::begin(), BaseClass::end(), c), BaseClass::end());
    }

    String createReversed() const
    {
        String reversed = *this;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    void reverseInPlace()
    {
        std::reverse(BaseClass::begin(), BaseClass::end());
    }

    Vector<size_t> findAll(const String& substring) const
    {
        Vector<size_t> results;
        for (size_t pos = BaseClass::find(substring); pos != String::npos; pos = BaseClass::find(substring, pos + 1))
        {
            results.push_back(pos);
        }
        return results;
    }
};

} // namespace moszir
