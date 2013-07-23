#ifndef IVIEWER_T977IO6T
#define IVIEWER_T977IO6T

#include <SDL.h>
#include "detail/grid.hpp"
#include "detail/position.hpp"

namespace game {

class iviewer
{
public:
    virtual ~iviewer() { }
    virtual void quit() = 0;
    virtual void render() = 0;
    virtual void clear_board() = 0;
    virtual void show_grid(const detail::position&, detail::color_t) = 0;
    virtual void show_match(const detail::position&) = 0;
    virtual void select_item(const detail::position&) = 0;
    virtual void show_text(const std::string& str, int x, int y, SDL_Color, int) = 0;
};

} // namespace game

#endif

