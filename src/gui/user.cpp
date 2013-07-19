#include <SDL.h>
#include "gui/user.hpp"
#include "events.hpp"

namespace game {
namespace gui {

user::user(boost::shared_ptr<controller_t> c, boost::shared_ptr<iviewer> v)
    : controller_(c), v_(v)
{ }

void user::run() {
    SDL_Event event;
    while (!controller_->is_flag_active<flags::game_over>()) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                default: break;

                case SDL_MOUSEBUTTONDOWN:
                    controller_->process_event(button_clicked(event.button));
                    break;

                case SDL_KEYDOWN:
                    controller_->process_event(key_pressed(event.key.keysym.sym));
                    break;

                case SDL_QUIT: //user closes the window
                    controller_->process_event(window_close());
                    break;
            }
        }
    }
}

} // namespace gui
} // namespace game

