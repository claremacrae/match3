#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include <SDL.h>
#include "detail/position.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

//flags
class flag_game_over { };

//events
typedef euml::True_ anonymous;

struct button_clicked : euml::euml_event<button_clicked>
{
    button_clicked() { }

    explicit button_clicked(const SDL_Event& event)
        : x(event.button.x), y(event.button.y)
    { }

    int x = 0;
    int y = 0;
};

struct key_pressed : euml::euml_event<key_pressed>
{
    key_pressed() { }

    explicit key_pressed(const SDL_Event& event)
        : key(event.key.keysym.sym)
    { }

    int key = 0;
};

struct window_close : euml::euml_event<window_close> { };
struct time_tick : euml::euml_event<time_tick> { };

} // namespace game

#endif

