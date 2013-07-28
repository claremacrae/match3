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
    static void ctor(shared_ptr<game::controller_t> //clients
                   , shared_ptr<game::gui::time>
                   , shared_ptr<game::gui::user>
    );
};

} // namespace di
} // namespace boost

namespace game {

typedef di::generic_module<
    di::bind_int    < _S("win width"),              755             >
  , di::bind_int    < _S("win height"),             600             >
  , di::bind_string < _S("win caption"),            _S("game")      >
  , di::bind_int    < _S("game time in seconds"),   60              >
  , di::bind_int    < _S("board rows"),             8               >
  , di::bind_int    < _S("board cols"),             8               >
  , di::bind_int    < _S("board winning strike"),   3               >
  , di::bind_int    < _S("board colors"),           4               >
  , di::bind_int    < _S("grid size"),              38              >
  , di::bind_int    < _S("grid offset"),            38 + 5          >
  , di::bind_int    < _S("grids offset x"),         328             >
  , di::bind_int    < _S("grids offset y"),         100             >
  , di::bind_string < _S("font name"),              _S("font.ttf")  >

  , di::singletons<
        sdl::window
      , controller_t
      , board
      , gui::user
      , gui::time
      , gui::viewer
      , points
      , time_ticks
      , random_rand
    >
> config;

} // namespace game

#endif

