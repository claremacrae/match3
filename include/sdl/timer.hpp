#ifndef TIMER_NKQ1WP9I
#define TIMER_NKQ1WP9I

#include <functional>
#include <SDL.h>

namespace match3 {
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
    SDL_TimerID id_ = 0;
};

} // namespace sdl
} // namespace match3

#endif

