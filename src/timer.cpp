#include <thread>
#include <iostream>
#include "timer.hpp"
#include "events.hpp"

namespace game {

timer::timer(const boost::shared_ptr<controller_t>& c, boost::di::named<int, game_time_in_sec> t)
    : controller_(c), time_in_sec_(t)
{ }

void timer::run() {
    std::this_thread::sleep_for(std::chrono::seconds(time_in_sec_));
    controller_->process_event(game_timeout());
}

} // namespace game

