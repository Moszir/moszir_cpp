#include "moszir/vector.hpp"

#include "gtest/gtest.h"


TEST(VectorEquals, PoC)
{
    moszir::Vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    moszir::Vector<int> w{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    moszir::Vector<int> z{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 555};
    EXPECT_TRUE(v.equals(v));
    EXPECT_TRUE(v.equals(w));
    EXPECT_TRUE(w.equals(v));
    EXPECT_TRUE(w.equals(w));

    EXPECT_FALSE(v.equals(z));
    EXPECT_FALSE(w.equals(z));
    EXPECT_FALSE(z.equals(v));
    EXPECT_FALSE(z.equals(w));
}

TEST(VectorEquals, Empty)
{
    moszir::Vector<int> v{};

    EXPECT_TRUE(v.equals(moszir::Vector<int>{}));

    EXPECT_FALSE(v.equals(moszir::Vector<int>{0}));
    EXPECT_FALSE(v.equals(moszir::Vector<int>{1}));
}

TEST(VectorEquals, Single)
{
    moszir::Vector<int> v{42};

    EXPECT_TRUE(v.equals(moszir::Vector<int>{42}));

    EXPECT_FALSE(v.equals(moszir::Vector<int>{}));
    EXPECT_FALSE(v.equals(moszir::Vector<int>{43}));
    EXPECT_FALSE(v.equals(moszir::Vector<int>{42, 42}));
}

TEST(VectorEquals, StdVector)
{
    moszir::Vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector w{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector z{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 555};
    EXPECT_TRUE(v.equals(w));
    EXPECT_TRUE(v == w);
    EXPECT_TRUE(w == v);
    EXPECT_FALSE(v != w);
    EXPECT_FALSE(w != v);

    EXPECT_FALSE(v.equals(z));
    EXPECT_FALSE(v == z);
    EXPECT_FALSE(z == v);
    EXPECT_TRUE(v != z);
    EXPECT_TRUE(z != v);
}

TEST(VectorEquals, Span)
{
    moszir::Vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::span<const int> w{v.data(), v.size()};
    std::span z{w.data(), w.size() - 1};
    EXPECT_TRUE(v.equals(w));
    EXPECT_FALSE(v.equals(z));
}
