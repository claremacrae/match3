#ifndef BOARD_CHK90LJU
#define BOARD_CHK90LJU

#include <cassert>
#include <vector>
#include <functional>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <mpl_string.hpp>
#include "detail/row.hpp"
#include "detail/position.hpp"
#include "irandom.hpp"

namespace game {

class board
{
    typedef std::vector<detail::row> rows_t;

public:
    BOOST_DI_CTOR(board
      , boost::di::named<int, _S("board rows")>
      , boost::di::named<int, _S("board cols")>
      , boost::di::named<int, _S("board winning strike")>
      , boost::di::named<int, _S("board colors")> colors
      , boost::shared_ptr<irandom>);

    void init_with_randoms();
    bool is_within_board(const detail::position& pos) const;
    bool is_neighbor(const detail::position&) const;
    bool is_same_selected(const detail::position&) const;
    bool is_same_color(const detail::position&);
    bool is_swap_winning();
    std::vector<detail::position> matches();

    void select(const detail::position&);
    void unselect_item(std::size_t);
    void unselect_all();
    void swap();
    void scroll_down();

    void set(const detail::position&, const detail::color_t&);
    detail::color_t get_grid_color(const detail::position&);

    int get_rows() const;
    int get_cols() const;
    int get_to_win() const;
    detail::color_t get_random() const;

private:
    bool is_swap_winning(const detail::position&);
    bool is_swap_winning_impl_x(const detail::position&);
    bool is_swap_winning_impl_y(const detail::position&);

    void matches(const detail::position&);
    void matches_impl_x(const detail::position&);
    void matches_impl_y(const detail::position&);
    void scroll_column(int, int);
    void clear_matches();

    int rows_size_;
    int cols_size_;
    int to_win_size_;
    int colors_;
    boost::shared_ptr<irandom> random_;
    rows_t rows_;
    mutable std::vector<detail::position> selected_;
};

} // namespace game

#endif

