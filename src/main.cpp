#include <boost/di.hpp>
#include "game.hpp"
#include "config.hpp"

#ifdef _WIN32
# undef main // for undefined reference to WinMain
#endif

int main() {
    match3::config().create<match3::game>().play();
    return 0;
}

