#pragma once

#include "fsm/types/types.h"
#include "fsm/utils/static_string.h"

class do_nothing
{
public:
	template <typename Machine, typename State, typename Event>
	void execute(Machine&, State&, const Event&)
	{
	}
};

static constexpr auto stringify(types<do_nothing>) { return static_string{"do_nothing"}; }
