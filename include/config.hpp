#ifndef CONFIG_2BXW6AE7
#define CONFIG_2BXW6AE7

#include <boost/di.hpp>
#include <mpl/string.hpp>
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
struct ctor_traits<match3::game>
{
    BOOST_DI_INJECT_TRAITS(
        std::shared_ptr<match3::controller_t>
      , named<std::shared_ptr<match3::iclient>, _S("time")> // non blocking
      , named<std::shared_ptr<match3::iclient>, _S("user")> // blocking
    );
};

} // namespace di
} // namespace boost

namespace match3 {

class config
{
    using implementations = di::injector<
        sdl::window
      , controller_t
      , board
      , gui::viewer
      , points
      , time_ticks
      , random_rand
      , di::bind<gui::time>::named<_S("time")>
      , di::bind<gui::user>::named<_S("user")>
    >;

public:
    auto configure() const {
        return di::make_injector(
            implementations()
          , di::bind<int>::named<_S("win width")>::to(755)
          , di::bind<int>::named<_S("win height")>::to(600)
          , di::bind<int>::named<_S("game time in seconds")>::to(60)
          , di::bind<int>::named<_S("board rows")>::to(8)
          , di::bind<int>::named<_S("board cols")>::to(8)
          , di::bind<int>::named<_S("board winning strike")>::to(3)
          , di::bind<int>::named<_S("board colors")>::to(5)
          , di::bind<std::string>::named<_S("win caption")>::to("game")
        );
    }
};

} // namespace match3

#endif

