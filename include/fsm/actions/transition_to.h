#pragma once

#include <fsm/types/Types.h>

template <typename TargetState>
class transition_to
{
public:
	template <typename Machine, typename State, typename Event>
	void execute(Machine& machine, State& prevState, const Event& event)
	{
        leave(prevState, event);
		TargetState& newState = machine.template transitionTo<TargetState>();
        enter(newState, event);
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
static constexpr auto stringify(Types<transition_to<State>>) { return static_string{"transition_to<"} + stringify(Types<State>{}) + static_string{">"}; }
