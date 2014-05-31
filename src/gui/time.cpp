#include <SDL.h>
#include "gui/time.hpp"
#include "events.hpp"

namespace match3 {
namespace gui {

time::time(std::shared_ptr<controller_t> c)
    : controller_(c)
{ }

void time::run() {
    timer_.reset(new sdl::timer(
        ONE_SECOND_IN_MILLISECONDS
      , [&](sdl::milliseconds_t interval) -> sdl::milliseconds_t {
            if (controller_->is_flag_active<flag_game_over>()) {
                return 0;
            }

            controller_->process_event(time_tick());
            return interval; //periodic
        }
    ));
}

} // namespace gui
} // namespace match3

