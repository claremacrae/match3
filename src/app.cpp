#include <boost/ref.hpp>
#include <functional>
#include "app.hpp"
#include "gui/user.hpp"

namespace game {

void app::play() {
    controller_->start();

    for (auto& client : clients_) {
        client->run();
    }
}

} // namespace game

