#ifndef POSITION_IZC7KE4U
#define POSITION_IZC7KE4U

namespace game {

struct position
{
    explicit position(int x = 0, int y = 0)
        : x(x), y(y)
    { }

    int x = 0;
    int y = 0;
};

inline bool operator<(const position& lhs, const position& rhs) {
    return lhs.x < rhs.x || lhs.y < rhs.y;
}

} // namespace game

#endif

