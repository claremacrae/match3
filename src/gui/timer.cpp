#include "gui/timer.hpp"
#include "events.hpp"

namespace game {
namespace gui {

namespace {

Uint32 callback(Uint32 interval, void *arg) {
    controller_t* c = static_cast<controller_t*>(arg);

    if (c->is_flag_active<flags::game_over>()) {
        return 0;
    }

    c->process_event(time_tick());
    return interval; //periodic
}

} // namespace

timer::timer(boost::shared_ptr<controller_t> c)
    : controller_(c)
{ }

void timer::run() {
    //old, c style, interface, even bind can't be used
    SDL_AddTimer(TICK_IN_MILLISECONDS, &callback, static_cast<void*>(controller_.get()));
}

} // namespace gui
} // namespace game

