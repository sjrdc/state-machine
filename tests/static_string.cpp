#include "fsm/utils/static_string.h"

#include "gtest/gtest.h"

using namespace fsm;

TEST(static_string, can_concatenate)
{
    constexpr static_string lhs{ "abc" };
    constexpr static_string rhs{ "de" };
    constexpr static_string expected{ "abcde" };
    static_assert(expected == lhs + rhs);
    EXPECT_EQ(lhs + rhs, expected);
}

TEST(static_string, string_reports_its_length)
{
    constexpr static_string lhs{ "abc" };
    constexpr size_t expected{ 3 };
    static_assert(lhs.length() == expected);
    EXPECT_EQ(lhs.length(), expected);
}

TEST(static_string, string_without_characters_has_length_0)
{
    constexpr static_string lhs{ "" };
    constexpr size_t expected{ 0 };
    static_assert(lhs.length() == expected);
    EXPECT_EQ(lhs.length(), expected);
}

TEST(static_string, string_length_can_be_compared)
{
    constexpr static_string shorter{ "abc" };
    constexpr static_string longer{ "abcdef" };
    constexpr static_string empty{ "" };

    constexpr size_t minLength{ 5 };
    constexpr static_string expectedShorter{ "abcxx" };
    constexpr static_string expectedLonger{ "abcde" };
    constexpr static_string expectedEmpty{ "zzzzz" };

    constexpr auto res = shorter.changeLength<minLength>('x');

    static_assert(res.data()[3] == expectedShorter.data()[3]);
    EXPECT_EQ(res.data()[3], expectedShorter.data()[3]);

    static_assert(shorter.changeLength<minLength>('x') == expectedShorter);
    EXPECT_EQ(shorter.changeLength<minLength>('x'), expectedShorter);
    static_assert(longer.changeLength<minLength>('y') == expectedLonger);
    EXPECT_EQ(longer.changeLength<minLength>('y'), expectedLonger);
    static_assert(empty.changeLength<minLength>('z') == expectedEmpty);
    EXPECT_EQ(empty.changeLength<minLength>('z'), expectedEmpty);
}
