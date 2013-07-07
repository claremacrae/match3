#ifndef POSITION_IZC7KE4U
#define POSITION_IZC7KE4U

namespace game {
namespace detail {

struct position
{
    explicit position(int x = 0, int y = 0)
        : x(x), y(y)
    { }

    int x = 0;
    int y = 0;
};

} // namespace detail
} // namespace game

#endif

