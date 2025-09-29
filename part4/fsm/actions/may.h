#pragma once

#include "one_of.h"

template <typename Action>
class may : public one_of<Action, do_nothing>
{
public:
	using one_of<Action, do_nothing>::one_of;
};

template <typename Action>
static constexpr auto stringify(Types<may<Action>>) { return StaticString{"may<"} + stringify(Types<Action>{}) + StaticString{">"}; }
