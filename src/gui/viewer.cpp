#include <cassert>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"

namespace match3 {
namespace gui {

viewer::viewer(std::shared_ptr<sdl::iwindow> window, int colors)
    : window_(window)
{
    window_->draw(
        window_->load_image(images_dir + background_image)
      , 0
      , 0
      , background_layer
    );

    match_image_ = window_->load_image(images_dir + match_image);
    select_image_ = window_->load_image(images_dir + select_image);

    for (int i = 1; i <= colors; ++i) {
        grid_images_[static_cast<color_t>(i)] =
            window_->load_image(images_dir + boost::lexical_cast<std::string>(i) + ".png");
    }
}

void viewer::render(sdl::milliseconds_t delay) {
    window_->render_layers();
    SDL_Delay(delay);
}

void viewer::clear_board() {
    window_->clear(board_layer);
    window_->clear(board_actions_layer);
}

void viewer::show_match(const position& pos) {
    window_->draw(
        match_image_
      , grids_offset_x + (pos.x * grid_offset)
      , grids_offset_y + (pos.y * grid_offset)
      , board_actions_layer
    );
}

void viewer::show_grid(const position& pos, color_t color) {
    if (color) {
        assert(grid_images_.find(color) != grid_images_.end());
        window_->draw(
            grid_images_[color]
          , grids_offset_x + (pos.x * grid_offset)
          , grids_offset_y + (pos.y * grid_offset)
          , board_layer
        );
    }
}

void viewer::scroll_grid(const position& pos, color_t color) {
    assert(grid_images_.find(color) != grid_images_.end());
    window_->draw(
        grid_images_[color]
      , grids_offset_x + (pos.x * grid_offset)
      , grids_offset_y + (pos.y * grid_offset) - grids_offset_y
      , board_layer
    );
}

void viewer::select_item(const position& pos) {
    window_->draw(
        select_image_
      , grids_offset_x + (pos.x * grid_offset) - 1
      , grids_offset_y + (pos.y * grid_offset) - 1
      , board_actions_layer
    );
}

void viewer::show_time(int seconds) {
    window_->clear(text_time_layer);
    show_text(
        boost::lexical_cast<std::string>(seconds) + " s"
      , 255
      , 555
      , black
      , 32
      , text_time_layer
    );
}

void viewer::show_points(int points) {
    window_->clear(text_points_layer);
    std::string points_ = boost::lexical_cast<std::string>(points);
    show_text(
        points_
      , 105 - (12 * (points_.length() - 1))
      , 435
      , black
      , 40
      , text_points_layer
    );
}

void viewer::show_results(int points) {
    window_->clear();
    std::string points_ = boost::lexical_cast<std::string>(points);
    show_text(
        "Points: " + points_
      , 180 - (30 * (points_.length() - 1))
      , 215
      , white
      , 100
      , background_layer
    );
}

void viewer::show_text(const std::string& str, int x, int y, SDL_Color color, int font_size, std::size_t layer) {
    window_->draw(
        window_->render_text(str, font, color, font_size)
      , x
      , y
      , layer
    );
}

void viewer::fade_screen(sdl::milliseconds_t delay) {
    for (Uint8 i = SDL_ALPHA_TRANSPARENT; i < SDL_ALPHA_OPAQUE; i += 5) {
        window_->fade(i/5);
        window_->render();
        SDL_Delay(delay);
    }
}

void viewer::quit() {
    window_->quit();
}

} // namespace gui
} // namespace match3

