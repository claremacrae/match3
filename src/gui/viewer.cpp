#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"
#include "gui/common.hpp"

namespace game {
namespace gui {

viewer::viewer(
    boost::di::named<std::string, images_dir> images_dir
  , const boost::shared_ptr<gui::isdl>& s)
    : images_dir_(static_cast<std::string>(images_dir) + "/images/"), sdl_(s)
{ }

void viewer::init() {
    if (not background_image_) {
        background_image_ = sdl_->load_image(images_dir_ + background_image);
    }
    sdl_->apply_surface(background_image_);
}

void viewer::refresh() {
    sdl_->refresh();
}

void viewer::show_match(const detail::position& pos) {
    if (not match_image_) {
        match_image_ = sdl_->load_image(images_dir_ + match_image);
    }
    sdl_->apply_surface(
        match_image_
      , grids_offset_x + pos.x * grid_offset
      , grids_offset_y + pos.y * grid_offset
    );
}

void viewer::show_grid(const detail::position& pos, detail::color_t color) {
    if (grid_images_.find(color) == grid_images_.end()) {
        grid_images_[color] = sdl_->load_image(images_dir_ + boost::lexical_cast<std::string>(color) + ".png");
    }
    sdl_->apply_surface(
        grid_images_[color]
      , grids_offset_x + pos.x * grid_offset
      , grids_offset_y + pos.y * grid_offset
    );
}

void viewer::select_item(const detail::position& pos) {
    sdl_->apply_surface(
        sdl_->load_image(images_dir_ + select_image)
      , grids_offset_x + (pos.x * grid_offset) - 1
      , grids_offset_y + (pos.y * grid_offset) - 1
    );
}

void viewer::stop() {
    sdl_->stop();
}

} // namespace gui
} // namespace game

