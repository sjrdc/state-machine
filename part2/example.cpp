#include "Door.h"

int main()
{
    door door{closed_state{}, open_state{}, locked_state{0}};

    door.handle(lock_event{1234});
    door.handle(unlock_event{2});
    door.handle(unlock_event{1234});

    return 0;
}
