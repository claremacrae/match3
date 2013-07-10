#include <boost/thread.hpp>
#include <iostream>
#include "gui/timer.hpp"
#include "events.hpp"

namespace game {
namespace gui {

timer::timer(boost::shared_ptr<controller_t> c)
    : controller_(c)
{ }

void timer::run() {
    while (!controller_->is_flag_active<flags::game_over>()) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        controller_->process_event(time_tick());
    }
}

} // namespace gui
} // namespace game

