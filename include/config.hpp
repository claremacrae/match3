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

namespace di = boost::di;

namespace match3 {

auto config() {
    return di::make_injector(
        di::bind<sdl::iwindow>.to<sdl::window>()
      , di::bind<iboard>.to<board>()
      , di::bind<iviewer>.to<gui::viewer>()
      , di::bind<ipoints>.to<points>()
      , di::bind<irandom>.to<random_rand>()
      , di::bind<int>.named("win_width"_s).to(755)
      , di::bind<int>.named("win_height"_s).to(600)
      , di::bind<int>.named("game_time_in_seconds"_s).to(60)
      , di::bind<int>.named("board_rows"_s).to(8)
      , di::bind<int>.named("board_cols"_s).to(8)
      , di::bind<int>.named("board_winning_strike"_s).to(3)
      , di::bind<int>.named("board_colors"_s).to(5)
      , di::bind<std::string>.named("win_caption"_s).to("game")
      , di::bind<iclient*[]>.to<gui::time/*non blocking*/, gui::user/*blocking*/>()
    );
};

} // namespace match3

#endif

