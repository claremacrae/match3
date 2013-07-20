#include <cassert>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"

namespace game {
namespace gui {

viewer::viewer(boost::shared_ptr<sdl::iwindow> w
             , boost::di::named<int, _S("grid offset")> g
             , boost::di::named<int, _S("grids offset x")> x
             , boost::di::named<int, _S("grids offset y")> y
             , boost::di::named<int, _S("board colors")> c
             , boost::di::named<std::string, _S("font name")> f
             , boost::di::named<int, _S("font size")> s)
    : window_(w)
    , grid_offset_(g)
    , grids_offset_x_(x)
    , grids_offset_y_(y)
    , colors_(c)
    , font_(f)
    , font_size_(s)
{
    background_image_ = window_->load_image(images_dir + background_image);
    match_image_ = window_->load_image(images_dir + match_image);
    select_image_ = window_->load_image(images_dir + select_image);

    for (int i = 0; i <= colors_; ++i) {
        grid_images_[static_cast<detail::color_t>(i)] =
            window_->load_image(images_dir + boost::lexical_cast<std::string>(i) + ".png");
    }
}

void viewer::set_background() {
    window_->clear();
    window_->draw(background_image_);
}

void viewer::render() {
    window_->render();
}

void viewer::show_match(const detail::position& pos) {
    window_->draw(
        match_image_
      , grids_offset_x_ + (pos.x * grid_offset_)
      , grids_offset_y_ + (pos.y * grid_offset_)
    );
}

void viewer::show_grid(const detail::position& pos, detail::color_t color) {
    assert(grid_images_.find(color) != grid_images_.end());
    window_->draw(
        grid_images_[color]
      , grids_offset_x_ + (pos.x * grid_offset_)
      , grids_offset_y_ + (pos.y * grid_offset_)
    );
}

void viewer::select_item(const detail::position& pos) {
    window_->draw(
        select_image_
      , grids_offset_x_ + (pos.x * grid_offset_) - 1
      , grids_offset_y_ + (pos.y * grid_offset_) - 1
    );
}

void viewer::show_text(const std::string& str, int x, int y) {
    std::cout << str << std::endl;
    window_->draw(window_->render_text(str, font_, {255, 255, 255, 0}, font_size_), x, y);
}

void viewer::quit() {
    window_->quit();
}

} // namespace gui
} // namespace game

