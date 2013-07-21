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

    explicit button_clicked(const SDL_MouseButtonEvent& button)
        : button(button)
    { }

    SDL_MouseButtonEvent button;
};

struct key_pressed : euml::euml_event<key_pressed>
{
    key_pressed() { }

    explicit key_pressed(int key)
        : key(key)
    { }

    int key = 0;
};

struct time_tick : euml::euml_event<time_tick> { };
struct window_close : euml::euml_event<window_close> { };

} // namespace game

#endif

