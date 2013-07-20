#ifndef GRID_5TY96XWJ
#define GRID_5TY96XWJ

#include "common.hpp"

namespace game {
namespace detail {

struct grid
{
    explicit grid(color_t c = 0)
        : color(c)
    { }

    color_t color = 0;
    bool matched = false;
};

} // namespace detail
} // namespace game

#endif

