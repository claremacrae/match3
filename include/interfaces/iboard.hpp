#ifndef IBOARD_TZCCH1TH
#define IBOARD_TZCCH1TH

#include <set>
#include "position.hpp"
#include "grid.hpp"

namespace game {

class iboard
{
public:
    virtual ~iboard() { };
    virtual void init_with_randoms() = 0;
    virtual bool is_within_board(const position&) const = 0;
    virtual bool is_neighbor(const position&) const = 0;
    virtual bool is_same_selected(const position&) const = 0;
    virtual bool is_same_color(const position&) = 0;
    virtual bool is_swap_winning() = 0;
    virtual bool are_selected() const = 0;
    virtual std::set<position> new_randoms() = 0;
    virtual std::set<position> matches() = 0;

    virtual void select(const position&) = 0;
    virtual void unselect_item(std::size_t) = 0;
    virtual void unselect_all() = 0;
    virtual void swap() = 0;
    virtual void scroll_down() = 0;

    virtual void set(const position&, const color_t&) = 0;
    virtual color_t get_grid_color(const position&) = 0;

    virtual int get_rows() const = 0;
    virtual int get_cols() const = 0;
    virtual int get_to_win() const = 0;
};

} // namespace game

#endif

