#include <boost/di.hpp>
#include "game.hpp"
#include "config.hpp"

#ifdef _WIN32
# undef main // for undefined reference to WinMain
#endif

int main() {
    auto injector = di::make_injector(match3::config());
    injector.create<match3::game>().play();

    return 0;
}

