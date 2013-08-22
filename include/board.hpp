#ifndef BOARD_CHK90LJU
#define BOARD_CHK90LJU

#include <cassert>
#include <vector>
#include <set>
#include <functional>
#include <cmath>
#include <memory>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <mpl/string.hpp>
#include "row.hpp"
#include "position.hpp"
#include "irandom.hpp"
#include "iboard.hpp"

namespace game {

class board : public iboard
{
    typedef std::vector<row> rows_t;

    friend std::ostream& operator<<(std::ostream&, board&);

public:
    BOOST_DI_CTOR(board
      , boost::di::named<int, _S("board rows")>
      , boost::di::named<int, _S("board cols")>
      , boost::di::named<int, _S("board winning strike")>
      , boost::di::named<int, _S("board colors")>
      , std::unique_ptr<irandom>);

    board(
        boost::di::named<int, _S("board rows")>
      , boost::di::named<int, _S("board cols")>
      , boost::di::named<int, _S("board winning strike")>
      , boost::di::named<int, _S("board colors")>
      , std::unique_ptr<irandom>
      , std::vector<color_t>);

    virtual void init_with_randoms() override;
    virtual bool is_within_board(const position&) const override;
    virtual bool is_neighbor(const position&) const override;
    virtual bool is_same_selected(const position&) const override;
    virtual bool is_same_color(const position&) override;
    virtual bool is_swap_winning() override;
    virtual bool are_selected() const override;
    virtual std::set<position> new_randoms() override;
    virtual std::set<position> matches() override;
    virtual std::set<position> scroll_down() override;

    virtual void select(const position&) override;
    virtual void unselect_all() override;
    virtual void swap() override;

    virtual color_t get_grid_color(const position&) override;

    virtual const_iterator begin() const override;
    virtual const_iterator end() const override;

private:
    bool is_item_winning(const position&);
    bool is_item_winning_impl_x(const position&);
    bool is_item_winning_impl_y(const position&);

    void matches(const position&, std::set<position>&);
    void matches_impl_x(const position&, std::set<position>&);
    void matches_impl_y(const position&, std::set<position>&);

    int rows_size_ = 0;
    int cols_size_ = 0;
    int to_win_size_ = 0;
    rows_t rows_;
    std::shared_ptr<irandom> random_;
    std::function<int()> random;
    mutable std::vector<position> selected_;
};

} // namespace game

#endif

