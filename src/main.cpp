#include <boost/shared_ptr.hpp>
#include <boost/di.hpp>
#include "app.hpp"
#include "config.hpp"

int main() {
    using namespace game;

    auto game_app = boost::di::injector<config>();
    game_app.create<boost::shared_ptr<app>>()->play();

    return 0;
}

