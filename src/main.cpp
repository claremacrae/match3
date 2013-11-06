#include <boost/di.hpp>
#include "app.hpp"
#include "config.hpp"

#ifdef _WIN32
# undef main // for undefined reference to WinMain
#endif

int main() {
    using namespace game;

    config().create<app>().play();

    return 0;
}

