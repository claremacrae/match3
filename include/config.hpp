#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
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
                   , shared_ptr<game::gui::user>
                   , shared_ptr<game::gui::time>
    );
};

} // namespace di
} // namespace boost

namespace game {

typedef di::generic_module<
    di::per_requests<
        di::bind<int, mpl::int_<8>>::in_name<rows>
      , di::bind<int, mpl::int_<8>>::in_name<cols>
      , di::bind<int, mpl::int_<3>>::in_name<to_win>
      , di::bind<int, mpl::int_<60>>::in_name<game_time_in_sec>
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

