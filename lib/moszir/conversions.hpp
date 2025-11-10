#pragma once

#include "string.hpp"
#include "vector.hpp"

#include <sstream>

namespace moszir
{

template <typename ValueType>
String toString(const Vector<ValueType>& vector, const std::string& separator = ", ")
{
    std::stringstream ss;
    vector.print(separator, ss);
    return String(ss.str());
}

template <typename ValueType>
String toString(const Vector<ValueType>& vector, const char separator)
{
    return toString(vector, std::string(1, separator));
}

} // namespace moszir
