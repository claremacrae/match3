#include <boost/di.hpp>
#include "app.hpp"
#include "config.hpp"

#ifdef _WIN32
# undef main // for undefined reference to WinMain
#endif

int main() {
    using namespace game;

    auto game_app = boost::di::injector<config>();
    game_app.create<app>().play();

    return 0;
}

