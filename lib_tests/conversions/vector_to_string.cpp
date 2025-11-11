/**
 * @file vector_to_string.cpp
 * @brief Unit tests for converting Vector to String.
 *
 * Variables to test:
 * - Size of the Vector (empty, single element, multiple elements)
 *   - To test whether the separator is handled correctly.
 * - Type of elements in the Vector (int, double, string, custom struct, nested Vector)
 * - Separator types (default ", ", custom character, custom string)
 */

#include "moszir/conversions.hpp"

#include "gtest/gtest.h"

namespace moszir
{

struct CustomStruct
{
    int a;
    double b;

    friend std::ostream& operator<<(std::ostream& os, const CustomStruct& cs)
    {
        return os << "{" << cs.a << ", " << cs.b << "}";
    }
};


TEST(ConversionsVectorToString, EmptyVector)
{
    EXPECT_EQ(String(), toString(Vector<int>{}));
    EXPECT_EQ(String(), toString(Vector<double>{}));
    EXPECT_EQ(String(), toString(Vector<String>{}));
    EXPECT_EQ(String(), toString(Vector<Vector<int>>{}));
    EXPECT_EQ(String(), toString(Vector<CustomStruct>{}));
}

TEST(ConversionsVectorToString, SingleElementVector)
{
    EXPECT_EQ(String("42"), toString(Vector<int>{42}));
    EXPECT_EQ(String("3.14"), toString(Vector<double>{3.14}));
    EXPECT_EQ(String("Hello"), toString(Vector<String>{String("Hello")}));
    EXPECT_EQ(String("1, 2, 3"), toString(Vector<Vector<int>>{Vector<int>{1, 2, 3}})); // The inner Vector is converted with default separator
    EXPECT_EQ(String("{7, 2.71}"), toString(Vector<CustomStruct>{CustomStruct{7, 2.71}}));
}

TEST(ConversionsVectorToString, MultipleElementsDefaultSeparator)
{
    EXPECT_EQ(String("1, 2, 3"), toString(Vector<int>{1, 2, 3}));
    EXPECT_EQ(String("1.1, 2.2, 3.3"), toString(Vector<double>{1.1, 2.2, 3.3}));
    EXPECT_EQ(String("Alpha, Beta, Gamma"), toString(Vector<String>{String("Alpha"), String("Beta"), String("Gamma")}));
    // Nested Vector flattens with default separator
    EXPECT_EQ(String("1, 2, 3, 4, 5, 6"), toString(Vector<Vector<int>>{Vector<int>{1, 2}, Vector<int>{3, 4}, Vector<int>{5, 6}}));
    EXPECT_EQ(String("{1, 1.1}, {2, 2.2}, {3, 3.3}"), toString(Vector<CustomStruct>{CustomStruct{1, 1.1}, CustomStruct{2, 2.2}, CustomStruct{3, 3.3}}));
}

TEST(ConversionsVectorToString, MultipleElementsCustomSeparator)
{
    EXPECT_EQ(String("1|2|3"), toString(Vector<int>{1, 2, 3}, '|'));
    EXPECT_EQ(String("1.1;2.2;3.3"), toString(Vector<double>{1.1, 2.2, 3.3}, ";"));
    EXPECT_EQ(String("Alpha - Beta - Gamma"), toString(Vector<String>{String("Alpha"), String("Beta"), String("Gamma")}, " - "));
    EXPECT_EQ(String("{1, 1.1} | {2, 2.2} | {3, 3.3}"), toString(Vector<CustomStruct>{CustomStruct{1, 1.1}, CustomStruct{2, 2.2}, CustomStruct{3, 3.3}}, " | "));

    // Inner Vectors use default separator
    EXPECT_EQ(String("1, 2; 3, 4; 5, 6"), toString(Vector<Vector<int>>{Vector<int>{1, 2}, Vector<int>{3, 4}, Vector<int>{5, 6}}, "; "));
    // which looks nice if there is only 1 level of nesting,
    // but can be confusing with deeper nesting
    // as the inner levels get "flattened" with default separator:
    EXPECT_EQ(
        String("1, 2, 3, 4; 5, 6"),
        toString(
            Vector<Vector<Vector<int>>>{
                Vector<Vector<int>>{Vector<int>{1, 2}, Vector<int>{3, 4}},
                Vector<Vector<int>>{Vector<int>{5, 6}},
            },
            "; "));
}

} // namespace moszir
