#include "moszir/vector.hpp"

#include "gtest/gtest.h"


TEST(VectorSort, PoC)
{
    moszir::Vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    v.sort();

    const auto expected = moszir::Vector<int>{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
    EXPECT_EQ(v, expected);
}

TEST(VectorSort, Empty)
{
    moszir::Vector<int> v{};
    v.sort();
    EXPECT_EQ(v, moszir::Vector<int>{});
}

TEST(VectorSort, Single)
{
    moszir::Vector<int> v{42};
    v.sort();
    EXPECT_EQ(v, moszir::Vector<int>{42});
}
