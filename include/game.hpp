#ifndef GAME_F6TO27D7
#define GAME_F6TO27D7

#include <memory>
#include <vector>
#include "controller.hpp"
#include "iclient.hpp"

namespace match3 {

class game
{
public:
    explicit game(const std::shared_ptr<controller_t>& c, const std::vector<std::shared_ptr<iclient>>& clients)
        : controller_(c), clients_(clients)
    { }

    void play();

private:
    std::shared_ptr<controller_t> controller_;
    std::vector<std::shared_ptr<iclient>> clients_;
};

} // namespace match3

#endif

