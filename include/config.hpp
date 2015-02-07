#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include "sdl/window.hpp"
#include "gui/viewer.hpp"
#include "gui/user.hpp"
#include "gui/time.hpp"
#include "iclient.hpp"
#include "controller.hpp"
#include "board.hpp"
#include "points.hpp"
#include "random_mt19937.hpp"
#include "random_rand.hpp"

namespace di  = boost::di;

namespace boost {
namespace di {

template<>
struct ctor_traits<match3::game> {
    BOOST_DI_INJECT_TRAITS(
        std::shared_ptr<match3::controller_t>
      , (named = match3::time) std::shared_ptr<match3::iclient> // non blocking
      , (named = match3::user) std::shared_ptr<match3::iclient> // blocking
    );
};

} // namespace di
} // namespace boost

namespace match3 {

class config {
public:
    auto configure() const {
        return di::make_injector(
            di::bind<sdl::iwindow, sdl::window>
          , di::bind<iboard, board>
          , di::bind<iviewer, gui::viewer>
          , di::bind<ipoints, points>
          , di::bind<irandom, random_rand>
          , di::bind<iclient, gui::time>.named(time)
          , di::bind<iclient, gui::user>.named(user)
          , di::bind<int>.named(win_width).to(755)
          , di::bind<int>.named(win_height).to(600)
          , di::bind<int>.named(game_time_in_seconds).to(60)
          , di::bind<int>.named(board_rows).to(8)
          , di::bind<int>.named(board_cols).to(8)
          , di::bind<int>.named(board_winning_strike).to(3)
          , di::bind<int>.named(board_colors).to(5)
          , di::bind<std::string>.named(win_caption).to("game")
        );
    }
};

} // namespace match3

#endif

