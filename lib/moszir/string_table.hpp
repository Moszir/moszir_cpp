#pragma once

#include "ifstream.hpp"
#include "string.hpp"
#include "vector.hpp"

#include <functional>

namespace moszir
{

class StringTable
{
public:

    StringTable() = default;

    StringTable(Ifstream& in)
    {
        while (in)
        {
            if (auto line = in.readLine();
                !line.empty())
            {
                table_.push_back(line);
            }
        }
    }

    bool checkRowSizes() const
    {
        return table_.empty()
            || table_.all_of([this](const auto& line) { return line.size() == table_.front().size(); });
    }

    auto begin() const { return table_.begin(); }
    auto end() const { return table_.end(); }

    size_t rowSize() const { return table_.size(); }
    size_t columnSize() const { return table_.empty() ? 0 : table_.front().size(); }

    const String& operator[](size_t index) const
    {
        return table_[index];
    }

    #pragma region Find Methods
    void findWords(
        const String& word,
        const std::function<void(size_t row, size_t col)>& callback) const
    {
        // Horizontal
        findWordsInternal<HorizontalDirection::LeftToRight, VerticalDirection::Stationary>(word, callback);
        findWordsInternal<HorizontalDirection::RightToLeft, VerticalDirection::Stationary>(word, callback);

        // Vertical
        findWordsInternal<HorizontalDirection::Stationary, VerticalDirection::TopToBottom>(word, callback);
        findWordsInternal<HorizontalDirection::Stationary, VerticalDirection::BottomToTop>(word, callback);

        // Diagonal
        findWordsInternal<HorizontalDirection::LeftToRight, VerticalDirection::TopToBottom>(word, callback);
        findWordsInternal<HorizontalDirection::RightToLeft, VerticalDirection::TopToBottom>(word, callback);
        findWordsInternal<HorizontalDirection::LeftToRight, VerticalDirection::BottomToTop>(word, callback);
        findWordsInternal<HorizontalDirection::RightToLeft, VerticalDirection::BottomToTop>(word, callback);
    }
    #pragma endregion

private:

    Vector<String> table_;

    enum class HorizontalDirection
    {
        LeftToRight,
        Stationary,
        RightToLeft
    };

    enum class VerticalDirection
    {
        TopToBottom,
        Stationary,
        BottomToTop
    };

    template<HorizontalDirection HDir, VerticalDirection VDir>
    void findWordsInternal(
        const String& word,
        const std::function<void(size_t row, size_t col)>& callback) const
    {
        static_assert(HDir != HorizontalDirection::Stationary || VDir != VerticalDirection::Stationary,
            "At least one direction must be non-stationary.");

        if (word.empty())
        {
            return;
        }

        constexpr int hStep = (HDir == HorizontalDirection::LeftToRight) ? 1
                            : (HDir == HorizontalDirection::RightToLeft) ? -1
                            : 0;
        constexpr int vStep = (VDir == VerticalDirection::TopToBottom) ? 1
                            : (VDir == VerticalDirection::BottomToTop) ? -1
                            : 0;
        const size_t startRow = (vStep == -1) ? word.size() - 1 : 0;
        const size_t endRow = (vStep == 1) ? rowSize() - word.size() + 1 : rowSize();
        const size_t startCol = (hStep == -1) ? word.size() - 1 : 0;
        const size_t endCol = (hStep == 1) ? columnSize() - word.size() + 1 : columnSize();
        for (size_t row = startRow; row < endRow; ++row)
        {
            for (size_t col = startCol; col < endCol; ++col)
            {
                bool match = true;
                for (size_t i = 0; i < word.size(); ++i)
                {
                    if (table_[row + i * vStep][col + i * hStep] != word[i])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    callback(row, col);
                }
            }
        }
    }
};

} // namespace moszir
