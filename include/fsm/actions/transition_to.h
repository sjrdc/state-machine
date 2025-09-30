#pragma once

#include "fsm/types/types.h"
#include "fsm/utils/static_string.h"


template <typename TargetState>
class transition_to
{
public:
	template <typename Machine, typename State, typename Event>
	void execute(Machine& machine, State& prev_state, const Event& event)
	{
        leave(prev_state, event);
		auto& next_state = machine.template transitionTo<TargetState>();
        enter(next_state, event);
	}

private:
    void leave(...)
    {
    }

    template <typename State, typename Event>
    auto leave(State& state, const Event& event) -> decltype(state.onLeave(event))
    {
        return state.onLeave(event);
    }

    void enter(...)
    {
    }

    template <typename State, typename Event>
    auto enter(State& state, const Event& event) -> decltype(state.onEnter(event))
    {
        return state.onEnter(event);
    }
};

template <typename State>
static constexpr auto stringify(types<transition_to<State>>) { return static_string{"transition_to<"} + stringify(types<State>{}) + static_string{">"}; }
