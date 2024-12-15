#pragma once

#include <fstream>

namespace moszir
{

/**
 * @brief An <c>std::ifstream</c> with additional functionality.
 */
class Ifstream : public std::ifstream
{
    using BaseClass = std::ifstream;
    using This = Ifstream;

public:

    using BaseClass::BaseClass;

    /**
     * @brief Returns whether the next character in the stream is an end of line character without consuming it.
     *
     * @return <c>true</c> if the next character is an end of line character, <c>false</c> otherwise.
     *
     * @note The function is not marked as <c>const</c> because the <c>peek</c> function is not <c>const</c>.
     */
    bool isEndOfLineNext()
    {
        return peek() == '\n' || peek() == '\r' || peek() == EOF;
    }

    /**
     * @brief Ignores the characters in the stream while they are end of line characters.
     */
    void ignoreEndOfLines()
    {
        while (peek() == '\n' || peek() == '\r')
        {
            ignore();
        }
    }
};

} // namespace moszir
