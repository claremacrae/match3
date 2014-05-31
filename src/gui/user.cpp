#include <SDL.h>
#include "gui/user.hpp"
#include "events.hpp"

namespace match3 {
namespace gui {

user::user(std::shared_ptr<controller_t> c)
    : controller_(c)
{ }

void user::run() {
    SDL_Event event = { };
    while (!controller_->is_flag_active<flag_game_over>()) {
        while (SDL_PollEvent(&event)) {
            controller_->process_event(event);
        }
    }
}

} // namespace gui
} // namespace match3

