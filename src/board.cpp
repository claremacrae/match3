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
    , rows_(get_rows(), row(get_cols()))
{ }

void board::init_with_randoms() {
   for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            rows_[x][y].color = random_->get_random_number(1, colors_);
        }
    }
}

bool board::is_within_board(const position& pos) const {
    int x = pos.x;
    int y = pos.y;

    return x >= 0 and x < get_cols() and
           y >= 0 and y < get_rows();
}

bool board::is_neighbor(const position& pos) const {
    assert(!selected_.empty());
    int x1 = pos.x;
    int y1 = pos.y;
    int x2 = selected_.back().x;
    int y2 = selected_.back().y;

    return (std::abs(x1 - x2) + std::abs(y1 - y2)) == 1;
}

bool board::is_same_selected(const position& pos) const {
    assert(selected_.size() == 1);
    return selected_[0].x == pos.x and selected_[0].y == pos.y;
}

bool board::is_same_color(const position& pos) {
    assert(selected_.size() == 1);
    return get_grid_color(selected_[0]) == get_grid_color(pos);
}

bool board::is_swap_winning() {
    assert(selected_.size() == 2);
    return is_swap_winning(selected_[0]) or
           is_swap_winning(selected_[1]);
}

bool board::are_selected() const {
    return !selected_.empty();
}

std::set<position> board::matches(const position& pos) {
    std::set<position> positions;
    matches(pos, positions);

    for (const auto& pos : positions) {
        rows_[pos.x][pos.y].color = grid::none;
    }

    return positions;
}

std::set<position> board::matches() {
    std::set<position> positions;

    for (const auto& item : selected_) {
        matches(item, positions);
    }

    for (const auto& pos : positions) {
        rows_[pos.x][pos.y].color = grid::none;
    }

    return positions;
}

std::set<position> board::new_randoms() {
    std::set<position> positions;

    for (int y = 0; y < get_rows(); ++y) {
        for (int x = 0; x < get_cols(); ++x) {
            if (rows_[x][y].color == grid::none) {
                rows_[x][y].color = random_->get_random_number(1, colors_);
                positions.insert(position(x, y));
            }
        }
    }

    return positions;
}

void board::select(const position& pos) {
    if (selected_.size() == 2) {
        selected_.clear();
    }
    selected_.push_back(position(pos.x, pos.y));
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

    color_t tmp = rows_[x1][y1].color;
    rows_[x1][y1].color = rows_[x2][y2].color;
    rows_[x2][y2].color = tmp;
}

void board::set(const position& pos, const color_t& color) {
    assert(pos.x >= 0 and pos.x < get_cols());
    assert(pos.y >= 0 and pos.y < get_rows());
    rows_[pos.x][pos.y].color = color;
}

color_t board::get_grid_color(const position& pos) {
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
            if (rows_[x][y].color == grid::none) {
                scroll_column(x, y);
                rows_[x][0].color = grid::none;
            }
        }
    }
}

bool board::is_swap_winning(const position& pos) {
    return is_swap_winning_impl_x(pos) or
           is_swap_winning_impl_y(pos);
}

bool board::is_swap_winning_impl_x(const position& pos) {
    color_t color = rows_[pos.x][pos.y].color;
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

bool board::is_swap_winning_impl_y(const position& pos) {
    color_t color = rows_[pos.x][pos.y].color;
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

void board::matches(const position& pos, std::set<position>& positions) {
    if (is_swap_winning_impl_x(pos)) {
        matches_impl_x(pos, positions);
    }

    if (is_swap_winning_impl_y(pos)) {
        matches_impl_y(pos, positions);
    }
}

void board::matches_impl_x(const position& pos, std::set<position>& positions) {
    color_t color = rows_[pos.x][pos.y].color;

    for (int x = pos.x; x < get_cols(); ++x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        positions.insert(position(x, pos.y));
    }

    for (int x = pos.x; x >= 0; --x) {
        if (rows_[x][pos.y].color != color) {
            break;
        }

        positions.insert(position(x, pos.y));
    }
}

void board::matches_impl_y(const position& pos, std::set<position>& positions) {
    color_t color = rows_[pos.x][pos.y].color;

    for (int y = pos.y; y < get_rows(); ++y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        positions.insert(position(pos.x, y));
    }

    for (int y = pos.y; y >= 0; --y) {
        if (rows_[pos.x][y].color != color) {
            break;
        }

        positions.insert(position(pos.x, y));
    }
}

int board::get_rows() const { return rows_size_; }
int board::get_cols() const { return cols_size_; }
int board::get_to_win() const { return to_win_size_; }

} // namespace game

