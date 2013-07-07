#include <thread>
#include <functional>
#include "app.hpp"

namespace game {

app::app(
    const boost::shared_ptr<controller_t>& c
  , const boost::shared_ptr<iclient>& l
  , const boost::shared_ptr<timer>& t)
    : controller_(c), client_(l), timer_(t)
{ }

void app::play() {
    controller_->start();
    std::thread timer(std::bind(&timer::run, *timer_));
    std::thread client(std::bind(&iclient::run, std::ref(*client_)));
    timer.join();
    client.join();
    controller_->stop();
}

} // namespace game

