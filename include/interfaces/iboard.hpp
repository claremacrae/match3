#ifndef IBOARD_TZCCH1TH
#define IBOARD_TZCCH1TH

#include <set>
#include "position.hpp"
#include "grid.hpp"

namespace game {

class iboard
{
public:
    class const_iterator
    {
    public:
        const_iterator(int rows, int cols, int x, int y)
            : rows(rows), cols(cols), x(x), y(y)
        { }

        const_iterator(const const_iterator& copy)
            : rows(copy.rows), cols(copy.cols), x(copy.x), y(copy.y)
        { }

        const_iterator& operator++() {
            if (++x >= cols and y < rows) {
                x = 0;
                y++;
            }

            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            operator++();
            return tmp;
        }

        bool operator==(const const_iterator& rhs) const {
            return position(x, y) == position(rhs.x, rhs.y);
        }

        bool operator!=(const const_iterator& rhs) const {
            return position(x, y) != position(rhs.x, rhs.y);
        }

        position operator*() {
            return position(x, y);
        }

    private:
        int rows = 0;
        int cols = 0;
        int x = 0;
        int y = 0;
    };

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
    virtual std::set<position> scroll_down() = 0;

    virtual void select(const position&) = 0;
    virtual void unselect_item(std::size_t) = 0;
    virtual void unselect_all() = 0;
    virtual void swap() = 0;

    virtual color_t get_grid_color(const position&) = 0;

    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
};

} // namespace game

#endif

