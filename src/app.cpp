#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include <functional>
#include "app.hpp"
#include "gui/user.hpp"

#include "SDL.h"
namespace game {

app::app(
    boost::shared_ptr<controller_t> c
  , boost::shared_ptr<iclient> u)
  //, boost::di::named<boost::shared_ptr<iclient>, user> u
  //, boost::di::named<boost::shared_ptr<iclient>, timer> t)
    : controller_(c), user_(u)//, timer_(t)
{ }

void app::play() {
    controller_->start();
    boost::thread user(boost::bind(&iclient::run, boost::ref(*user_)));
    //boost::thread timer(boost::bind(&iclient::run, boost::ref(*timer_)));
    user.join();
    //timer.join();
}

} // namespace game

