#pragma once

#include <fsm/types/Types.h>

#include <utility>

class resolve_action
{
public:
    template <typename State, typename Event>
    constexpr auto operator()(Types<State, Event>)
    {
        using Action = decltype(std::declval<State>().handle(std::declval<Event>()));
        return Types<Action>{};
    }

    template <typename State, typename Event>
    constexpr auto operator()(Types<Types<State, Event>>)
    {
        return (*this)(Types<State, Event>{});
    }
};
