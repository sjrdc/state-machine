#pragma once

#include "fsm/state_machine.h"
#include "fsm/actions/do_nothing.h"
#include "fsm/actions/transition_to.h"
#include "fsm/actions/may.h"
#include "fsm/actions/by_default.h"
#include "fsm/actions/on.h"
#include "fsm/actions/will.h"

#include <cstdint>

struct open_event
{
};

struct close_event
{
};

struct lock_event
{
    uint32_t new_key;    
};

struct unlock_event
{
    uint32_t key;    
};

struct closed_state;
struct open_state;
class locked_state;

struct closed_state : public fsm::will<fsm::by_default<fsm::do_nothing>,
                                           fsm::on<lock_event, fsm::transition_to<locked_state>>,
                                           fsm::on<open_event, fsm::transition_to<open_state>>>
{
};

struct open_state : public fsm::will<fsm::by_default<fsm::do_nothing>,
                                         fsm::on<close_event, fsm::transition_to<closed_state>>>
{
};

class locked_state : public fsm::by_default<fsm::do_nothing>
{
public:
    using by_default::handle;

    locked_state(uint32_t key)
        : key(key)
    {
    }

    void on_enter(const lock_event& e)
    {
        key = e.new_key;
    }

    fsm::may<fsm::transition_to<closed_state>> handle(const unlock_event& e)
    {
        if (e.key == key) {
            return fsm::transition_to<closed_state>{};
        }
        return fsm::do_nothing{};
    }

private:
    uint32_t key;
};

using door = fsm::state_machine<closed_state, open_state, locked_state>;
