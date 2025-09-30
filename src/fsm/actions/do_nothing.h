#pragma once

class do_nothing
{
public:
	template <typename Machine, typename State, typename Event>
	void execute(Machine&, State&, const Event&)
	{
	}
};

static constexpr auto stringify(Types<do_nothing>) { return static_string{"do_nothing"}; }
