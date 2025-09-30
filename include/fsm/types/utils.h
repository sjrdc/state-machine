#pragma once

#include "fsm/types/types.h"

template <typename Operation>
class map_and_join
{
public:
    constexpr map_and_join(Operation operation)
        : operation(std::move(operation))
    {
    }

    template <typename... Ts>
    constexpr auto operator()(types<Ts>... rhs)
    {
        return (operation(rhs) + ...);
    }

private:
    Operation operation;
};
