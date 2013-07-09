#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include "detail/position.hpp"

namespace game {

struct item_selected
{
    explicit item_selected(const detail::position& pos)
        : pos(pos)
    { }

    detail::position pos;
};

struct time_tick { };
struct key_pressed { };
struct window_close { };

} // namespace game

#endif

