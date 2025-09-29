#pragma once

template <typename Event, typename Action>
struct on
{
	Action handle(const Event&) const
	{
		return Action{};
	}
};

