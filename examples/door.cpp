#include <fsm/types/Types.h>
#include <fsm/actions/utils.h>
#include <fsm/types/utils.h>
#include <fsm/utils/static_string.h>

#include "door.h"

#include <iostream>


#define STRINGIFY_IMPL(TYPE) static constexpr auto stringify(Types<TYPE>) { return static_string{#TYPE}; }

STRINGIFY_IMPL(open_event)
STRINGIFY_IMPL(close_event)
STRINGIFY_IMPL(lock_event)
STRINGIFY_IMPL(unlock_event)

STRINGIFY_IMPL(closed_state)
STRINGIFY_IMPL(open_state)
STRINGIFY_IMPL(locked_state)

struct Header {};

struct SimpleStringifier
{
    constexpr auto operator()(Types<Header>) const
    {
        return static_string{""};
    }

    template <typename T>
    constexpr auto operator()(Types<T> type) const
    {
        return stringify(type);
    }
};

template <std::size_t Width>
struct ConstantWidthStringifier
{
    constexpr auto operator()(Types<Header>) const
    {
        return static_string{""}.template changeLength<Width>(' ');
    }

    template <typename T>
    constexpr auto operator()(Types<T> type) const
    {
        return stringify(type).template changeLength<Width>(' ');
    }
};

template <typename Stringifier, typename State>
class GenerateRow
{
public:
    constexpr GenerateRow(Stringifier str, Types<State>)
        : str(str)
    {
    }

    constexpr auto operator()(Types<State> state) const
    {
        return str(state);
    }

    template <typename Event>
    constexpr auto operator()(Types<Event>) const
    {
        auto action = resolve_action{}(Types<Types<State, Event>>{});
        return static_string{" | "} + str(action);
    }

private:
    const Stringifier str;
};

template <typename Stringifier>
class GenerateRow<Stringifier, Header>
{
public:
    constexpr GenerateRow(Stringifier str, Types<Header>)
        : str(str)
    {
    }

    constexpr auto operator()(Types<Header> header) const
    {
        return str(header);
    }

    template <typename Event>
    constexpr auto operator()(Types<Event> event) const
    {
        return static_string{" | "} + str(event);
    }

private:
    const Stringifier str;
};

template <typename Stringifier, typename... Events>
class GenerateTable
{
public:
    constexpr GenerateTable(Stringifier str, Types<Events...>)
        : str(str)
    {
    }

    template <typename State>
    constexpr auto operator()(Types<State> state) const
    {
        return (Types<State, Events...>{} | MapAndJoin{GenerateRow{str, state}}) + static_string{"\n"};
    }

private:
    const Stringifier str;
};

template <std::size_t X>
struct Maximum
{
    template <std::size_t Y>
    constexpr auto operator+(Maximum<Y>) const
    {
        return Maximum<std::max(X, Y)>{};
    }

    static constexpr auto value()
    {
        return X;
    }
};

struct CalculateMaxLength
{
    template <typename T>
    constexpr auto operator()(Types<T> type)
    {
        return Maximum<stringify(type).length()>{};
    }
};

template <typename... StateTypes, typename... EventTypes>
constexpr auto generateTransitionTable(Types<StateTypes...> states, Types<EventTypes...> events)
{
    constexpr SimpleStringifier stringifier;
    constexpr auto result = (Types<Header>{} + states) | MapAndJoin{GenerateTable{stringifier, events}};
    return result;
}

template <typename... StateTypes, typename... EventTypes>
constexpr auto generatePrettyTransitionTable(Types<StateTypes...> states, Types<EventTypes...> events)
{
    constexpr auto actions = (states * events) | MapAndJoin(resolve_action{});
    constexpr auto maxWidth = (states + events + actions) | MapAndJoin(CalculateMaxLength{});
    constexpr ConstantWidthStringifier<maxWidth.value()> stringifier{};
    constexpr auto result = (Types<Header>{} + states) | MapAndJoin{GenerateTable{stringifier, events}};
    return result;
}

int main()
{
    std::cout << generateTransitionTable(door::getStateTypes(), Types<open_event, close_event, lock_event, unlock_event>{}).data() << std::endl;
    std::cout << generatePrettyTransitionTable(door::getStateTypes(), Types<open_event, close_event, lock_event, unlock_event>{}).data() << std::endl;
    return 0;
}
