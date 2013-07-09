#include <SDL/SDL.h>
#include "gui/client.hpp"
#include "gui/common.hpp"
#include "detail/position.hpp"
#include "events.hpp"

namespace game {
namespace gui {

client::client(const boost::shared_ptr<controller_t>& c)
    : controller_(c)
{ }

void client::run() {
    SDL_Event event;

    while (!controller_->is_flag_active<flags::game_over>()) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                default: break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        detail::position pos(
                            (event.button.x - grids_offset_x) / grid_offset
                          , (event.button.y - grids_offset_y) / grid_offset
                        );
                        controller_->process_event(item_selected(pos));
                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        controller_->process_event(key_pressed());
                    }
                    break;
            }
        }
    }
}

} // namespace gui
} // namespace game

