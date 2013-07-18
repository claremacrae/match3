#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include <boost/msm/front/euml/euml.hpp>
#include "detail/position.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

typedef euml::kleene_ any;

struct item_selected : euml::euml_event<item_selected>
{
    item_selected() { }

    explicit item_selected(const detail::position& pos)
        : pos(pos)
    { }

    detail::position pos;
};

struct time_tick : euml::euml_event<time_tick> { };
struct key_pressed : euml::euml_event<key_pressed> { };
struct window_close : euml::euml_event<window_close>{ };

} // namespace game

#endif

