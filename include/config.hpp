#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include "gui/sdl.hpp"
#include "gui/viewer.hpp"
#include "gui/client.hpp"
#include "random.hpp"

namespace di  = boost::di;
namespace mpl = boost::mpl;

namespace game {

typedef di::generic_module<
    di::per_requests<
        di::bind<int, mpl::int_<8>>::in_name<rows>
      , di::bind<int, mpl::int_<8>>::in_name<cols>
      , di::bind<int, mpl::int_<3>>::in_name<to_win>
      , di::bind<int, mpl::int_<60>>::in_name<game_time_in_sec>
    >

  , di::singletons<
        gui::viewer
      , gui::client
      , gui::sdl
      , random
      , controller_t
    >

  , di::externals<
        di::annotate<
            di::bind<std::string>::in_name<gui::images_dir>
        >::with<gui::images_dir>
    >
> config;

} // namespace game

#endif

