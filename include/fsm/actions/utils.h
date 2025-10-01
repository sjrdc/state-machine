#pragma once

#include "fsm/types/types.h"

#include <utility>

namespace fsm
{
    class resolve_action
    {
    public:
        template <typename State, typename Event>
        constexpr auto operator()(types<State, Event>)
        {
            using Action = decltype(std::declval<State>().handle(std::declval<Event>()));
            return types<Action>{};
        }

        template <typename State, typename Event>
        constexpr auto operator()(types<types<State, Event>>)
        {
            return (*this)(types<State, Event>{});
        }
    };
}
