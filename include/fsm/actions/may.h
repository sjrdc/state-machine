#pragma once

#include "fsm/actions/one_of.h"
#include "fsm/types/types.h"

template <typename Action>
class may : public one_of<Action, do_nothing>
{
public:
	using one_of<Action, do_nothing>::one_of;
};

template <typename Action>
static constexpr auto stringify(types<may<Action>>) { return static_string{"may<"} + stringify(types<Action>{}) + static_string{">"}; }
