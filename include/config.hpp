#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include "gui/window.hpp"
#include "gui/viewer.hpp"
#include "gui/user.hpp"
#include "gui/timer.hpp"
#include "random_mt19937.hpp"
#include "random_rand.hpp"

namespace di  = boost::di;
namespace mpl = boost::mpl;

namespace game {
class user { };
class timer { };
} // namespace game

namespace boost {
namespace di {

using namespace game;

template<>
struct ctor_traits<game::app>
{
    static void ctor(shared_ptr<controller_t>
                   , named<shared_ptr<iclient>, user>
                   , named<shared_ptr<iclient>, timer>
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
        di::bind<iclient, gui::user>::in_name<user>
      , di::bind<iclient, gui::timer>::in_name<timer>
      , gui::viewer
      , gui::window
      , random_rand
      , controller_t
    >
> config;

} // namespace game

#endif

