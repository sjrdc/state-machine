#pragma once

#include <fsm/utils/array_utils.h>

#include <iostream>

template <std::size_t N>
class static_string
{
public:
    constexpr static_string(const char (&chars)[N])
        : chars(toStdArray(chars))
    {
    }

    constexpr static_string(const std::array<const char, N>& chars)
        : chars(chars)
    {
    }

    template <std::size_t M>
    constexpr static_string<N + M - 1> operator+(const static_string<M> &rhs) const
    {
        return join(resize<N-1>(chars, '\0'), rhs.chars);
    }

    constexpr bool operator==(const static_string<N> &rhs) const
    {
        return areEqual(chars, rhs.chars);
    }

    constexpr std::size_t length() const
    {
        return N - 1;
    }

    template <std::size_t TargetLen>
    constexpr static_string<TargetLen + 1> changeLength(char fill) const
    {
        constexpr std::array<const char, 1> stringEnd{'\0'};
        return join(resize<TargetLen>(resize<N-1>(chars, fill), fill), stringEnd);
    }

    template <std::size_t M>
    friend class static_string;

    constexpr const char* data() const
    {
        return chars.data();
    }

private:
    std::array<const char, N> chars;
};

namespace tests
{
namespace
{

[[maybe_unused]] constexpr void testAdding()
{
    constexpr static_string lhs{"abc"};
    constexpr static_string rhs{"de"};
    constexpr static_string expected{"abcde"};
    static_assert(expected == lhs + rhs);
}

[[maybe_unused]] constexpr void testLength()
{
    constexpr static_string lhs{"abc"};
    constexpr size_t expected{3};
    static_assert(lhs.length() == expected);
}

[[maybe_unused]] constexpr void test0Length()
{
    constexpr static_string lhs{""};
    constexpr size_t expected{0};
    static_assert(lhs.length() == expected);
}

[[maybe_unused]] constexpr void testChangeLength()
{
    constexpr static_string shorter{"abc"};
    constexpr static_string longer{"abcdef"};
    constexpr static_string empty{""};

    constexpr size_t minLength{5};
    constexpr static_string expectedShorter{"abcxx"};
    constexpr static_string expectedLonger {"abcde"};
    constexpr static_string expectedEmpty  {"zzzzz"};

    constexpr auto res = shorter.changeLength<minLength>('x');

    static_assert(res.data()[3] == expectedShorter.data()[3]);

    static_assert(shorter.changeLength<minLength>('x') == expectedShorter);
    static_assert(longer.changeLength<minLength>('y') == expectedLonger);
    static_assert(empty.changeLength<minLength>('z') == expectedEmpty);
}

}
}
