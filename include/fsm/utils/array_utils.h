#pragma once

#include <array>
#include <type_traits>
namespace fsm
{
    template <typename T, std::size_t N, std::size_t... Idx>
    constexpr std::array<T, N> toStdArray(T (&arr)[N], std::index_sequence<Idx...>)
    {
        return {arr[Idx]...};
    }

    template <typename T, std::size_t N>
    constexpr std::array<T, N> toStdArray(T (&arr)[N])
    {
        return toStdArray(arr, std::make_index_sequence<N>());
    }

    template <typename T, std::size_t LeftSize, std::size_t RightSize, std::size_t... LeftIdx, std::size_t... RightIdx>
    constexpr std::array<T, LeftSize + RightSize> join(const std::array<T, LeftSize>& lhs, const std::array<T, RightSize>& rhs, std::index_sequence<LeftIdx...>, std::index_sequence<RightIdx...>)
    {
        return {lhs[LeftIdx]..., rhs[RightIdx]...};
    }

    template <typename T, std::size_t LeftSize, std::size_t RightSize>
    constexpr std::array<T, LeftSize + RightSize> join(const std::array<T, LeftSize>& lhs, const std::array<T, RightSize>& rhs)
    {
        return join(lhs, rhs, std::make_index_sequence<LeftSize>(), std::make_index_sequence<RightSize>());
    }

    template <std::size_t NewSize, typename T, std::size_t OldSize, std::size_t... Indexes>
    constexpr std::array<T, NewSize> resize(const std::array<T, OldSize>& arr, std::remove_const_t<T> defaultValue, std::index_sequence<Indexes...>)
    {
        return {((Indexes < OldSize) ? arr[Indexes] : defaultValue)...};
    }

    template <std::size_t NewSize, typename T, std::size_t OldSize>
    constexpr std::array<T, NewSize> resize(const std::array<T, OldSize>& arr, std::remove_const_t<T> defaultValue)
    {
        return resize<NewSize>(arr, defaultValue, std::make_index_sequence<NewSize>());
    }

    template <typename T, std::size_t N, std::size_t... Idx>
    constexpr bool areEqual(const std::array<T, N>& lhs, const std::array<T, N>& rhs, std::index_sequence<Idx...>)
    {
        return ((lhs[Idx] == rhs[Idx]) && ...);
    }

    template <typename T, std::size_t N>
    constexpr bool areEqual(const std::array<T, N>& lhs, const std::array<T, N>& rhs)
    {
        return areEqual(lhs, rhs, std::make_index_sequence<N>());
    }
}