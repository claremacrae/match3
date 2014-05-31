#ifndef IVIEWER_T977IO6T
#define IVIEWER_T977IO6T

#include <SDL.h>
#include "sdl/timer.hpp"
#include "grid.hpp"
#include "position.hpp"

namespace match3 {

class iviewer
{
public:
    virtual ~iviewer() { }
    virtual void quit() = 0;
    virtual void render(sdl::milliseconds_t = 0) = 0;
    virtual void clear_board() = 0;
    virtual void show_grid(const position&, color_t) = 0;
    virtual void scroll_grid(const position&, color_t) = 0;
    virtual void show_match(const position&) = 0;
    virtual void select_item(const position&) = 0;
    virtual void show_time(int) = 0;
    virtual void show_points(int) = 0;
    virtual void show_results(int) = 0;
    virtual void fade_screen(sdl::milliseconds_t = 0) = 0;
};

} // namespace match3

#endif

