#include "fsm/types/types.h"
#include "fsm/actions/utils.h"
#include "fsm/types/utils.h"
#include "fsm/utils/static_string.h"

#include "door.h"

#include <iostream>


#define STRINGIFY_IMPL(TYPE) static constexpr auto stringify(types<TYPE>) { return static_string{#TYPE}; }

STRINGIFY_IMPL(open_event)
STRINGIFY_IMPL(close_event)
STRINGIFY_IMPL(lock_event)
STRINGIFY_IMPL(unlock_event)

STRINGIFY_IMPL(closed_state)
STRINGIFY_IMPL(open_state)
STRINGIFY_IMPL(locked_state)

struct header {};

struct simple_stringifier
{
    constexpr auto operator()(types<header>) const
    {
        return static_string{""};
    }

    template <typename T>
    constexpr auto operator()(types<T> type) const
    {
        return stringify(type);
    }
};

template <std::size_t Width>
struct constant_width_stringifier
{
    constexpr auto operator()(types<header>) const
    {
        return static_string{""}.template changeLength<Width>(' ');
    }

    template <typename T>
    constexpr auto operator()(types<T> type) const
    {
        return stringify(type).template changeLength<Width>(' ');
    }
};

template <typename Stringifier, typename State>
class generate_row
{
public:
    constexpr generate_row(Stringifier str, types<State>)
        : str(str)
    {
    }

    constexpr auto operator()(types<State> state) const
    {
        return str(state);
    }

    template <typename Event>
    constexpr auto operator()(types<Event>) const
    {
        auto action = resolve_action{}(types<types<State, Event>>{});
        return static_string{" | "} + str(action);
    }

private:
    const Stringifier str;
};

template <typename Stringifier>
class generate_row<Stringifier, header>
{
public:
    constexpr generate_row(Stringifier str, types<header>)
        : str(str)
    {
    }

    constexpr auto operator()(types<header> header) const
    {
        return str(header);
    }

    template <typename Event>
    constexpr auto operator()(types<Event> event) const
    {
        return static_string{" | "} + str(event);
    }

private:
    const Stringifier str;
};

template <typename Stringifier, typename... Events>
class generate_table
{
public:
    constexpr generate_table(Stringifier str, types<Events...>)
        : str(str)
    {
    }

    template <typename State>
    constexpr auto operator()(types<State> state) const
    {
        return (types<State, Events...>{} | map_and_join{generate_row{str, state}}) + static_string{"\n"};
    }

private:
    const Stringifier str;
};

template <std::size_t X>
struct maximum
{
    template <std::size_t Y>
    constexpr auto operator+(maximum<Y>) const
    {
        return maximum<std::max(X, Y)>{};
    }

    static constexpr auto value()
    {
        return X;
    }
};

struct calculate_max_length
{
    template <typename T>
    constexpr auto operator()(types<T> type)
    {
        return maximum<stringify(type).length()>{};
    }
};

template <typename... StateTypes, typename... EventTypes>
constexpr auto generate_transition_table(types<StateTypes...> states, types<EventTypes...> events)
{
    constexpr simple_stringifier stringifier;
    constexpr auto result = (types<header>{} + states) | map_and_join{generate_table{stringifier, events}};
    return result;
}

template <typename... StateTypes, typename... EventTypes>
constexpr auto generate_pretty_transition_table(types<StateTypes...> states, types<EventTypes...> events)
{
    constexpr auto actions = (states * events) | map_and_join(resolve_action{});
    constexpr auto maxWidth = (states + events + actions) | map_and_join(calculate_max_length{});
    constexpr constant_width_stringifier<maxWidth.value()> stringifier{};
    constexpr auto result = (types<header>{} + states) | map_and_join{generate_table{stringifier, events}};
    return result;
}

int main()
{
    std::cout << generate_transition_table(door::getStateTypes(), types<open_event, close_event, lock_event, unlock_event>{}).data() << std::endl;
    std::cout << generate_pretty_transition_table(door::getStateTypes(), types<open_event, close_event, lock_event, unlock_event>{}).data() << std::endl;
    return 0;
}
