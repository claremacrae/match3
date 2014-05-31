#include <boost/ref.hpp>
#include <functional>
#include "game.hpp"
#include "gui/user.hpp"

namespace match3 {

void game::play() {
    controller_->start();

    for (auto& client : clients_) {
        client->run();
    }
}

} // namespace match3

