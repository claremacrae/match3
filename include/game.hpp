#ifndef GAME_F6TO27D7
#define GAME_F6TO27D7

#include <memory>
#include "controller.hpp"
#include "iclient.hpp"

namespace match3 {

class game
{
public:
    template<typename... TClients>
    explicit game(std::shared_ptr<controller_t> c, TClients&&... cl)
        : controller_(c), clients_{std::forward<TClients>(cl)...}
    { }

    void play();

private:
    std::shared_ptr<controller_t> controller_;
    std::vector<std::shared_ptr<iclient>> clients_;
};

} // namespace match3

#endif

