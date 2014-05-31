#include "points.hpp"

namespace match3 {

void points::add(int n) {
    points_ += n;
}

void points::sub(int n) {
    points_ -= n;
}

points::operator int() const {
    return points_;
}

} // namespace match3

