#ifndef TIMER_NKQ1WP9I
#define TIMER_NKQ1WP9I

#include <functional>
#include <SDL.h>

namespace game {
namespace sdl {

typedef Uint32 milliseconds_t;

class timer
{
    typedef std::function<milliseconds_t(milliseconds_t)> callback_t;

public:
    timer(milliseconds_t, const callback_t&);
    ~timer();

private:
    static milliseconds_t do_callback(milliseconds_t, void*);

    callback_t callback_;
    SDL_TimerID id_;
};

} // namespace sdl
} // namespace game

#endif

