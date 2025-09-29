#pragma once

template <typename Action>
class by_default
{
public:
	template <typename Event>
	Action handle(const Event&) const
	{
		return Action{};
	}
};
