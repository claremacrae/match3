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
struct ctor_traits<match3::game>
{
    //clients
    BOOST_DI_INJECT_TRAITS(std::shared_ptr<match3::controller_t>
                         , std::shared_ptr<match3::gui::time>
                         , std::shared_ptr<match3::gui::user>);
};

} // namespace di
} // namespace boost

namespace match3 {

typedef di::injector<

    di::bind_int    < 755        >::named< _S("win width")             >
  , di::bind_int    < 500        >::named< _S("win height")            >
  , di::bind_string < _S("game") >::named< _S("win caption")           >
  , di::bind_int    < 60         >::named< _S("game time in seconds")  >
  , di::bind_int    < 8          >::named< _S("board rows")            >
  , di::bind_int    < 8          >::named< _S("board cols")            >
  , di::bind_int    < 3          >::named< _S("board winning strike")  >
  , di::bind_int    < 5          >::named< _S("board colors")          >

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

} // namespace match3

#endif

