#include "board.hpp"
#include <cassert>
#include <functional>
#include <cmath>

namespace match3 {

board::board(
    int rows
  , int cols
  , int win
  , int colors
  , std::unique_ptr<irandom> r)
    : rows_size_(rows)
    , cols_size_(cols)
    , to_win_size_(win)
    , rows_(rows_size_, row(cols_size_))
    , random_(std::move(r))
    , random(std::bind(&irandom::get_random_number, std::ref(*random_), 1, static_cast<int>(colors)))
{ }

board::board(
    int rows
  , int cols
  , int win
  , int colors
  , std::unique_ptr<irandom> r
  , std::vector<color_t> v)
    : board(rows, cols, win, colors, std::move(r))
{
    int i = 0;
    for (const auto& pos : *this) {
        rows_[pos.x][pos.y].color = v[i++];
    }
}

void board::init_with_randoms() {
    for (const auto& pos : *this) {
        do {
            rows_[pos.x][pos.y].color = random();
        } while (is_item_winning(pos));
    }
}

bool board::is_within_board(const position& pos) const {
    int x = pos.x;
    int y = pos.y;

    return x >= 0 and x < cols_size_ and
           y >= 0 and y < rows_size_;
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
    return is_item_winning(selected_[0]) or
           is_item_winning(selected_[1]);
}

bool board::are_selected() const {
    return !selected_.empty();
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

    for (const auto& pos : *this) {
        if (rows_[pos.x][pos.y].color == grid::none) {
            rows_[pos.x][pos.y].color = random();
            positions.insert(pos);
        }
    }

    return positions;
}

void board::select(const position& pos) {
    selected_.push_back(position(pos.x, pos.y));
}

void board::unselect_all() {
    selected_.clear();
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

color_t board::get_grid_color(const position& pos) {
    assert(pos.x >= 0 and pos.x < cols_size_);
    assert(pos.y >= 0 and pos.y < rows_size_);
    return rows_[pos.x][pos.y].color;
}

std::set<position> board::scroll_down() {
    std::set<position> positions;

    auto scroll_column = [&](int x, int i) {
        for (int y = i; y > 0; --y) {
            rows_[x][y].color = rows_[x][y - 1].color;
        }
    };

    for (const auto& pos : *this) {
        if (rows_[pos.x][pos.y].color == grid::none) {
            scroll_column(pos.x, pos.y);
            rows_[pos.x][0].color = grid::none;
            positions.insert(pos);
        }
    }

    return positions;
}

bool board::is_item_winning(const position& pos) {
    return is_item_winning_impl_x(pos) or
           is_item_winning_impl_y(pos);
}

bool board::is_item_winning_impl_x(const position& pos) {
    color_t color = rows_[pos.x][pos.y].color;
    int length = 0;

    for (int x = pos.x; x < cols_size_; ++x) {
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

    return length >= to_win_size_ + 1;
}

bool board::is_item_winning_impl_y(const position& pos) {
    color_t color = rows_[pos.x][pos.y].color;
    int length = 0;

    for (int y = pos.y; y < rows_size_; ++y) {
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

    return length >= to_win_size_ + 1;
}

void board::matches(const position& pos, std::set<position>& positions) {
    if (is_item_winning_impl_x(pos)) {
        matches_impl_x(pos, positions);
    }

    if (is_item_winning_impl_y(pos)) {
        matches_impl_y(pos, positions);
    }
}

void board::matches_impl_x(const position& pos, std::set<position>& positions) {
    color_t color = rows_[pos.x][pos.y].color;

    for (int x = pos.x; x < cols_size_; ++x) {
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

    for (int y = pos.y; y < rows_size_; ++y) {
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

board::const_iterator board::begin() const {
    return const_iterator(rows_size_, cols_size_, 0, 0);
}

board::const_iterator board::end() const {
    return const_iterator(rows_size_, cols_size_, 0, cols_size_);
}

} // namespace match3

