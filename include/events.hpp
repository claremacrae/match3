#ifndef EVENTS_BCQLG30Q
#define EVENTS_BCQLG30Q

#include <boost/mpl/int.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <mpl/string.hpp>
#include <SDL.h>
#include "position.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

//flags
class flag_game_over { };

//events
typedef euml::True_ anonymous;

struct button_clicked : euml::euml_event<button_clicked>
{
    typedef mpl::int_<SDL_MOUSEBUTTONUP> id;

    button_clicked() { }

    BOOST_DI_CTOR(button_clicked
        , const SDL_Event& event
        , boost::di::named<int, _S("grid offset")> grid = 38 + 5
        , boost::di::named<int, _S("grids offset x")> x = 328
        , boost::di::named<int, _S("grids offset y")> y = 100)
        : pos(((event.button.x - x) / grid)
            , ((event.button.y - y) / grid))
    { }

    position pos;
};

struct key_pressed : euml::euml_event<key_pressed>
{
    typedef mpl::int_<SDL_KEYDOWN> id;

    key_pressed() { }

    explicit key_pressed(const SDL_Event& event)
        : key(event.key.keysym.sym)
    { }

    int key = 0;
};

struct window_close : euml::euml_event<window_close>
{
    typedef mpl::int_<SDL_QUIT> id;
};

struct time_tick : euml::euml_event<time_tick>
{
    typedef mpl::int_<__LINE__> id;
};

} // namespace game

#endif

