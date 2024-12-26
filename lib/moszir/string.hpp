#pragma once

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
};

} // namespace moszir
