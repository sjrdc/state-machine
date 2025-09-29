#pragma once

struct do_nothing
{
	template <typename Machine, typename State, typename Event>
	void execute(Machine&, State&, const Event&)
	{
	}
};
