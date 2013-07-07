#include <boost/shared_ptr.hpp>
#include <cassert>
#include <thread>
#include "controller.hpp"

namespace game {

controller::controller(
    const boost::shared_ptr<board>& b
  , const boost::shared_ptr<iviewer>& v
)
    : board_(b), viewer_(v)
{ }

void controller::show_board() {
    viewer_->init();
    for (int y = 0; y < board_->get_rows(); y++) {
        for (int x = 0; x < board_->get_cols(); x++) {
            detail::position pos(x, y);
            viewer_->show_grid(pos, board_->get_grid_color(pos));
        }
    }
    viewer_->refresh();
}

void controller::init_board(const msm::front::none&) {
    board_->init_with_randoms();
    show_board();
}

bool controller::is_within_board(const item_selected& event) {
    return board_->is_within_board(event.pos);
}

bool controller::is_neighbor(const item_selected& event) {
    return board_->is_neighbor(event.pos);
}

bool controller::is_correct_item(const item_selected& event) {
    return is_within_board(event) and is_neighbor(event);
}

bool controller::is_the_same_item(const item_selected& event) {
    return board_->is_same_selected(event.pos);
}

bool controller::is_swap_items_correct(const msm::front::none&) {
    return board_->is_swap_winning();
}

bool controller::is_swap_items_incorrect(const msm::front::none& event) {
    return !is_swap_items_correct(event);
}

void controller::select_item(const item_selected& event) {
    board_->select(event.pos);
    viewer_->select_item(event.pos);
    viewer_->refresh();
}

void controller::unselect_item(const item_selected&) {
    board_->unselect_all();
    show_board();
}

void controller::swap_items(const msm::front::none&) {
    board_->swap();
    show_board();
}

void controller::revert_swap_items(const msm::front::none&) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    board_->swap(); // just swap again
    board_->unselect_all();
    show_board();
}

void controller::show_matches(const msm::front::none&) {
    for (auto& pos : board_->matches()) {
        viewer_->show_match(pos);
    }
    board_->unselect_all();
    viewer_->refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void controller::scroll_board(const msm::front::none&) {
    board_->scroll_down();
    show_board();
}

void controller::finish_game(const game_timeout&) {
    is_finished = true;
    viewer_->refresh();
}

bool controller::finished() const {
    return is_finished;
}

} // namespace game

