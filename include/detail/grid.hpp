#ifndef GRID_5TY96XWJ
#define GRID_5TY96XWJ

#include "common.hpp"

namespace game {
namespace detail {

struct grid
{
    explicit grid(color_t c = black)
        : color(c)
    { }

    color_t color;
    bool matched = false;
};

} // namespace detail
} // namespace game

#endif

