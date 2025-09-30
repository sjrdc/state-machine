#pragma once

#include <cstddef>

template <typename... Ts>
struct types
{
};

template <typename... Lhs, typename... Rhs>
constexpr auto operator+(types<Lhs...>, types<Rhs...>)
{
    return types<Lhs..., Rhs...>{};
}

template <typename Lhs, typename... Rhs>
constexpr auto operator*(types<Lhs>, types<Rhs...>)
{
    return types<types<Lhs, Rhs>...>{};
}

template <typename... Lhs, typename Rhs>
constexpr auto operator*(types<Lhs...>, Rhs rhs)
{
    return ((types<Lhs>{} * rhs) + ...);
}

template <typename... Ts, typename Operation>
constexpr auto operator|(types<Ts...>, Operation oper)
{
    return oper(types<Ts>{}...);
}

template <typename... Ts>
constexpr std::size_t size(types<Ts...>)
{
    return sizeof...(Ts);
}
