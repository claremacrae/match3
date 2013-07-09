#include <thread>
#include <functional>
#include "app.hpp"

namespace game {

app::app(
    boost::shared_ptr<controller_t> c
  , boost::di::named<boost::shared_ptr<iclient>, user> u
  , boost::di::named<boost::shared_ptr<iclient>, timer> t)
    : controller_(c), user_(u), timer_(t)
{ }

void app::play() {
    controller_->start();
    std::thread user(std::bind(&iclient::run, std::ref(*user_)));
    std::thread timer(std::bind(&iclient::run, std::ref(*timer_)));
    timer.join();
    user.join();
    controller_->stop();
}

} // namespace game

