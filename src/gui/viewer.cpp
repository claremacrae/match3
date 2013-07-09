#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"
#include "gui/common.hpp"

namespace game {
namespace gui {

viewer::viewer(
    boost::di::named<std::string, images_dir> images_dir
  , boost::shared_ptr<gui::iwindow> s)
    : images_dir_(static_cast<std::string>(images_dir) + "/images/"), window_(s)
{ }

void viewer::init() {
    if (not background_image_) {
        background_image_ = window_->load_image(images_dir_ + background_image);
    }
    window_->apply(background_image_);
}

void viewer::render() {
    window_->render();
}

void viewer::show_match(const detail::position& pos) {
    if (not match_image_) {
        match_image_ = window_->load_image(images_dir_ + match_image);
    }
    window_->apply(
        match_image_
      , grids_offset_x + pos.x * grid_offset
      , grids_offset_y + pos.y * grid_offset
    );
}

void viewer::show_grid(const detail::position& pos, detail::color_t color) {
    if (grid_images_.find(color) == grid_images_.end()) {
        grid_images_[color] = window_->load_image(images_dir_ + boost::lexical_cast<std::string>(color) + ".png");
    }
    window_->apply(
        grid_images_[color]
      , grids_offset_x + pos.x * grid_offset
      , grids_offset_y + pos.y * grid_offset
    );
}

void viewer::select_item(const detail::position& pos) {
    window_->apply(
        window_->load_image(images_dir_ + select_image)
      , grids_offset_x + (pos.x * grid_offset) - 1
      , grids_offset_y + (pos.y * grid_offset) - 1
    );
}

void viewer::quit() {
    window_->quit();
}

} // namespace gui
} // namespace game

