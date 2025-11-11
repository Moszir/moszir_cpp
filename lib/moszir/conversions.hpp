#pragma once

#include "string.hpp"
#include "vector.hpp"

#include <sstream>

namespace moszir
{

/**
 * @brief Converts a Vector to a String with a specified separator.
 *
 * @tparam ValueType The type of the elements in the Vector.
 *
 * @param[in] vector
 * The Vector to convert.
 *
 * @param[in] separator
 * The separator to use between elements. Default is ", ".
 *
 * @return
 * A String representation of the Vector.
 */
template <typename ValueType>
String toString(const Vector<ValueType>& vector, const std::string& separator = ", ")
{
    std::stringstream ss;
    vector.print(separator, ss);
    return String(ss.str());
}

/**
 * @brief Converts a Vector to a String with a specified character separator.
 *
 * @tparam ValueType The type of the elements in the Vector.
 *
 * @param[in] vector
 * The Vector to convert.
 *
 * @param[in] separator
 * The character separator to use between elements.
 *
 * @return
 * A String representation of the Vector.
 */
template <typename ValueType>
String toString(const Vector<ValueType>& vector, const char separator)
{
    return toString(vector, std::string(1, separator));
}

} // namespace moszir
