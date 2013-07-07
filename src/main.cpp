#include <boost/shared_ptr.hpp>
#include <boost/di.hpp>
#include <libgen.h>
#include "app.hpp"
#include "config.hpp"

int main(int, char** argv) {
    using namespace game;

    auto game_app = boost::di::injector<config>(
        config(config::set<gui::images_dir>(dirname(argv[0])))
    );
    game_app.create<boost::shared_ptr<app>>()->play();

    return 0;
}

