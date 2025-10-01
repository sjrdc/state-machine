#pragma once

namespace fsm
{
    template <typename Event, typename Action>
    class on
    {
    public:
	    Action handle(const Event&) const
	    {
		    return Action{};
	    }
    };
}
