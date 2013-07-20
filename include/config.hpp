#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include <mpl_string.hpp>
#include "sdl/window.hpp"
#include "gui/viewer.hpp"
#include "gui/user.hpp"
#include "gui/time.hpp"
#include "random_mt19937.hpp"
#include "random_rand.hpp"

namespace di  = boost::di;
namespace mpl = boost::mpl;

namespace boost {
namespace di {

template<>
struct ctor_traits<game::app>
{
    static void ctor(shared_ptr<game::controller_t>
                   , shared_ptr<game::gui::time>
                   , shared_ptr<game::gui::user> // has to be in the main thread
    );
};

} // namespace di
} // namespace boost

namespace game {

typedef di::generic_module<
    di::per_requests<
        di::bind_int    < _S("rows"),                   8               >
      , di::bind_int    < _S("cols"),                   8               >
      , di::bind_int    < _S("winning strike"),         3               >
      , di::bind_int    < _S("game time in seconds"),   60              >
      , di::bind_int    < _S("min color"),              0               >
      , di::bind_int    < _S("max color"),              4               >
      , di::bind_int    < _S("grid size"),              38              >
      , di::bind_int    < _S("grid offset"),            38 + 5          >
      , di::bind_int    < _S("grid offset x"),          328             >
      , di::bind_int    < _S("grid offset y"),          100             >
      , di::bind_string < _S("font name"),              _S("font.ttf")  >
      , di::bind_int    < _S("font size"),              16              >
      , di::bind_int    < _S("win width"),              755             >
      , di::bind_int    < _S("win height"),             600             >
      , di::bind_string < _S("win caption"),            _S("game")      >
    >

  , di::singletons<
        sdl::window
      , gui::user
      , gui::time
      , gui::viewer
      , random_rand
      , controller_t
    >
> config;

} // namespace game

#endif

