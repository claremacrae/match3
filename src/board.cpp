#include "board.hpp"
#include <cassert>
#include <functional>
#include <cmath>

namespace game {

board::board(
    boost::di::named<int, _S("board rows")> rows
  , boost::di::named<int, _S("board cols")> cols
  , boost::di::named<int, _S("board winning strike")> win
  , boost::di::named<int, _S("board colors")> colors
  , boost::shared_ptr<irandom> i)
    : rows_size_(rows)
    , cols_size_(cols)
    , to_win_size_(win)
    , colors_(colors)
    , random_(i)
    , rows_(get_rows(), detail::row(get_cols()))
{ }

void board::init_with_randoms() {
   for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            rows_[x][y].color = get_random();
        }
    }
}

bool board::is_within_board(const detail::position& pos) const {
    int x = pos.x;
    int y = pos.y;

    return x >= 0 and x < get_cols() and
           y >= 0 and y < get_rows();
}

bool board::is_neighbor(const detail::position& pos) const {
    assert(!selected_.empty());
    int x1 = pos.x;
    int y1 = pos.y;
    int x2 = selected_.back().x;
    int y2 = selected_.back().y;

    return (std::abs(x1 - x2) + std::abs(y1 - y2)) == 1;
}

bool board::is_same_selected(const detail::position& pos) const {
    assert(selected_.size() == 1);
    return selected_[0].x == pos.x and selected_[0].y == pos.y;
}

bool board::is_same_color(const detail::position& pos) {
    assert(selected_.size() == 1);
    return get_grid_color(selected_[0]) == get_grid_color(pos);
}

bool board::is_swap_winning() {
    assert(selected_.size() == 2);
    return is_swap_winning(selected_[0]) or
           is_swap_winning(selected_[1]);
}

std::vector<detail::position> board::matches() {
    assert(selected_.size() == 2);

    clear_matches();
    matches(selected_[0]);
    matches(selected_[1]);

    std::vector<detail::position> v;
    for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            if (rows_[x][y].matched) {
                v.push_back(detail::position(x, y));
            }
        }
    }
    return v;
}

void board::select(const detail::position& pos) {
    if (selected_.size() == 2) {
        selected_.clear();
    }
    selected_.push_back(detail::position(pos.x, pos.y));
}

void board::unselect_all() {
    selected_.clear();
}

void board::unselect_item(std::size_t item) {
    assert(selected_.size() > item);
    selected_.erase(selected_.begin() + item);
}

void board::swap() {
    assert(selected_.size() == 2);
    int x1 = selected_[0].x;
    int y1 = selected_[0].y;
    int x2 = selected_[1].x;
    int y2 = selected_[1].y;

    detail::color_t tmp = rows_[x1][y1].color;
    rows_[x1][y1].color = rows_[x2][y2].color;
    rows_[x2][y2].color = tmp;
}

void board::set(const detail::position& pos, const detail::color_t& color) {
    assert(pos.x >= 0 and pos.x < get_cols());
    assert(pos.y >= 0 and pos.y < get_rows());
    rows_[pos.x][pos.y].color = color;
}

detail::color_t board::get_grid_color(const detail::position& pos) {
    assert(pos.x >= 0 and pos.x < get_cols());
    assert(pos.y >= 0 and pos.y < get_rows());
    return rows_[pos.x][pos.y].color;
}

void board::scroll_column(int x, int i) {
    for (int y = i; y > 0; --y) {
        rows_[x][y].color = rows_[x][y - 1].color;
    }
}

void board::scroll_down() {
    for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            if (rows_[x][y].matched) {
                scroll_column(x, y);
                rows_[x][0].color = get_random();
            }
        }
    }
    clear_matches();
}

bool board::is_swap_winning(const detail::position& pos) {
    return is_swap_winning_impl_x(pos) or
           is_swap_winning_impl_y(pos);
}

bool board::is_swap_winning_impl_x(const detail::position& pos) {
    detail::color_t color = rows_[pos.x][pos.y].color;
    int length = 0;

    for (int x = pos.x; x < get_cols(); ++x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        length++;
    }

    for (int x = pos.x; x >= 0; --x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        length++;
    }

    return length >= get_to_win() + 1;
}

bool board::is_swap_winning_impl_y(const detail::position& pos) {
    detail::color_t color = rows_[pos.x][pos.y].color;
    int length = 0;

    for (int y = pos.y; y < get_rows(); ++y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        length++;
    }

    for (int y = pos.y; y >= 0; --y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        length++;
    }

    return length >= get_to_win() + 1;
}

void board::matches(const detail::position& pos) {
    if (is_swap_winning_impl_x(pos)) {
        matches_impl_x(pos);
    }

    if (is_swap_winning_impl_y(pos)) {
        matches_impl_y(pos);
    }
}

void board::matches_impl_x(const detail::position& pos) {
    detail::color_t color = rows_[pos.x][pos.y].color;

    for (int x = pos.x; x < get_cols(); ++x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        rows_[x][pos.y].matched = true;
    }

    for (int x = pos.x; x >= 0; --x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        rows_[x][pos.y].matched = true;
    }
}

void board::matches_impl_y(const detail::position& pos) {
    detail::color_t color = rows_[pos.x][pos.y].color;

    for (int y = pos.y; y < get_rows(); ++y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        rows_[pos.x][y].matched = true;
    }

    for (int y = pos.y; y >= 0; --y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        rows_[pos.x][y].matched = true;
    }
}

void board::clear_matches() {
    for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            rows_[x][y].matched = false;
        }
    }
}

int board::get_rows() const { return rows_size_; }
int board::get_cols() const { return cols_size_; }
int board::get_to_win() const { return to_win_size_; }

detail::color_t board::get_random() const {
    return static_cast<detail::color_t>(
        random_->get_random_number(0, colors_)
    );
}

} // namespace game

