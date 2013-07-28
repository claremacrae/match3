#ifndef GRID_5TY96XWJ
#define GRID_5TY96XWJ

namespace game {

typedef int color_t;

struct grid
{
    explicit grid(color_t c = 0)
        : color(c)
    { }

    color_t color = 0;
    bool matched = false;
};

} // namespace game

#endif

