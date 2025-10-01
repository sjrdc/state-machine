#pragma once

#include "fsm/utils/array_utils.h"

#include <iostream>
namespace fsm
{
    template <std::size_t N>
    class static_string
    {
    public:
        constexpr static_string(const char(&chars)[N])
            : chars(toStdArray(chars))
        {
        }

        constexpr static_string(const std::array<const char, N>& chars)
            : chars(chars)
        {
        }

        template <std::size_t M>
        constexpr static_string<N + M - 1> operator+(const static_string<M>& rhs) const
        {
            return join(resize<N - 1>(chars, '\0'), rhs.chars);
        }

        constexpr bool operator==(const static_string<N>& rhs) const
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
            constexpr std::array<const char, 1> stringEnd{ '\0' };
            return join(resize<TargetLen>(resize<N - 1>(chars, fill), fill), stringEnd);
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
}
