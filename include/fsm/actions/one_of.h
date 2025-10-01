#pragma once

#include <utility>
#include <variant>
namespace fsm
{
	template <typename... Actions>
	class one_of
	{
	public:
		template <typename T>
		one_of(T&& arg)
			: actions(std::forward<T>(arg))
		{
		}

		template <typename Machine, typename State, typename Event>
		void execute(Machine& machine, State& state, const Event& event)
		{
			std::visit([&machine, &state, &event](auto& action) { action.execute(machine, state, event); }, actions);
		}

	private:
		std::variant<Actions...> actions;
	};
}
