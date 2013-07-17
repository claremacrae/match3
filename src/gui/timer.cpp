#include <boost/bind.hpp>
#include "gui/timer.hpp"
#include "events.hpp"

namespace game {
namespace gui {

timer::timer(boost::shared_ptr<controller_t> c)
    : controller_(c), callback_(boost::bind(&timer::callback, this, _1))
{ }

void timer::run() {
    SDL_AddTimer(TICK_IN_MILLISECONDS, &timer::do_callback, &callback_);
}

Uint32 timer::callback(Uint32 interval) {
    if (controller_->is_flag_active<flags::game_over>()) {
        return 0;
    }

    controller_->process_event(time_tick());
    return interval; //periodic
}

Uint32 timer::do_callback(Uint32 interval, void* data) {
    return (*static_cast<callback_t*>(data))(interval);
}

} // namespace gui
} // namespace game

