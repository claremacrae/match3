#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include <boost/mpl/int.hpp>
#include <boost/di/ctor.hpp>
#include <mpl/string.hpp>
#include <SDL.h>
#include "position.hpp"

namespace game {

template<typename T, int Id>
struct event : boost::msm::front::euml::euml_event<T>
{
    typedef boost::mpl::int_<Id> id;
};

//flags
class flag_game_over { };

//events
typedef boost::msm::front::euml::True_ anonymous;

struct button_clicked : event<button_clicked, SDL_MOUSEBUTTONUP>
{
    button_clicked() { }

    BOOST_DI_CTOR(button_clicked
        , const SDL_Event& event
        , int grid_offset = 38 + 5
        , int grids_offset_x = 328
        , int grids_offset_y = 100)
        : pos(((event.button.x - grids_offset_x) / grid_offset)
            , ((event.button.y - grids_offset_y) / grid_offset))
    { }

    position pos;
};

struct key_pressed : event<key_pressed, SDL_KEYDOWN>
{
    key_pressed() { }

    explicit key_pressed(const SDL_Event& event)
        : key(event.key.keysym.sym)
    { }

    int key = 0;
};

struct window_close : event<window_close, SDL_QUIT> { };
struct time_tick    : event<time_tick, __LINE__> { };

} // namespace game

#endif

