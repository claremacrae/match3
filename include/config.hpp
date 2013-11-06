#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include <mpl/string.hpp>
#include "sdl/window.hpp"
#include "gui/viewer.hpp"
#include "gui/user.hpp"
#include "gui/time.hpp"
#include "controller.hpp"
#include "board.hpp"
#include "points.hpp"
#include "random_mt19937.hpp"
#include "random_rand.hpp"

namespace di  = boost::di;

namespace boost {
namespace di {

template<>
struct ctor_traits<game::app>
{
    BOOST_DI_CTOR_TRAITS(shared_ptr<game::controller_t> //clients
                       , shared_ptr<game::gui::time>
                       , shared_ptr<game::gui::user>);
};

} // namespace di
} // namespace boost

namespace game {

typedef di::injector<

    di::bind_int    < 755        >::in_name< _S("win width")             >
  , di::bind_int    < 500        >::in_name< _S("win height")            >
  , di::bind_string < _S("game") >::in_name< _S("win caption")           >
  , di::bind_int    < 60         >::in_name< _S("game time in seconds")  >
  , di::bind_int    < 8          >::in_name< _S("board rows")            >
  , di::bind_int    < 8          >::in_name< _S("board cols")            >
  , di::bind_int    < 3          >::in_name< _S("board winning strike")  >
  , di::bind_int    < 5          >::in_name< _S("board colors")          >

  , sdl::window
  , controller_t
  , board
  , gui::user
  , gui::time
  , gui::viewer
  , points
  , time_ticks
  , random_rand

> config;

} // namespace game

#endif

