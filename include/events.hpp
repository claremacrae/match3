#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include <SDL.h>
#include "sdl/event.hpp"
#include "detail/position.hpp"

namespace game {

//flags
class flag_game_over { };

//events
struct button_clicked : sdl::event<button_clicked, __LINE__>
{
    button_clicked() { }

    explicit button_clicked(const SDL_MouseButtonEvent& button)
        : button(button)
    { }

    SDL_MouseButtonEvent button;
};

struct key_pressed : sdl::event<key_pressed, __LINE__>
{
    key_pressed() { }

    explicit key_pressed(int key)
        : key(key)
    { }

    int key = 0;
};

struct time_tick : sdl::event<time_tick, __LINE__> { };

struct window_close : sdl::event<window_close, __LINE__> { };

} // namespace game

#endif

