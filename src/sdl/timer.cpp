#include "sdl/timer.hpp"

namespace game {
namespace sdl {

timer::timer(milliseconds_t time, const callback_t& callback)
    : callback_(callback)
{
    id_ = SDL_AddTimer(time, &timer::do_callback, &callback_);
}

timer::~timer() {
    SDL_RemoveTimer(id_);
}

Uint32 timer::do_callback(milliseconds_t interval, void* data) {
    return (*static_cast<callback_t*>(data))(interval);
}

} // namespace sdl
} // namespace game

