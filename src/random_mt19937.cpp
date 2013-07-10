#include <random>
#include "random_mt19937.hpp"

namespace game {

int random_mt19937::get_random_number(int min, int max) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

} // namespace game

