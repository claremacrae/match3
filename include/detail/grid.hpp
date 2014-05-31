#ifndef GRID_5TY96XWJ
#define GRID_5TY96XWJ

namespace match3 {

typedef int color_t;

struct grid
{
    static const color_t none = 0;

    explicit grid(color_t c = 0)
        : color(c)
    { }

    color_t color = 0;
};

} // namespace match3

#endif

