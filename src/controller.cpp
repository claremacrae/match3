#include <SDL.h>
#include "controller.hpp"

namespace game {

controller::controller(
    boost::shared_ptr<board> b
  , boost::shared_ptr<iviewer> v
  , boost::di::named<int, _S("game time in seconds")> t
)
    : board_(b), viewer_(v), game_time_in_sec_(t)
{ }

} // namespace game

