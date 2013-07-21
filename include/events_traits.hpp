#ifndef EVENTS_TRAITS_PSKYP9K8
#define EVENTS_TRAITS_PSKYP9K8

#include <SDL.h>
#include "events.hpp"

namespace game {

template<typename T>
struct events_traits
{
    static const int id = -1; //invalid
};

template<>
struct events_traits<button_clicked>
{
    static const int id = SDL_MOUSEBUTTONUP;
};

template<>
struct events_traits<key_pressed>
{
    static const int id = SDL_KEYDOWN;
};

template<>
struct events_traits<window_close>
{
    static const int id = SDL_QUIT;
};

template<>
struct events_traits<time_tick>
{
    static const int id = __LINE__;
};

} // namespace game

#endif

