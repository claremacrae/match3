#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include <boost/shared_ptr.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/di/ctor.hpp>
#include "detail/position.hpp"
#include "events.hpp"
#include "board.hpp"

namespace game {

template<typename T>
class guard : public boost::msm::front::euml::euml_action<T>
{
public:
    BOOST_DI_CTOR(guard
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>())
        : board_(b)
    { }

protected:
    boost::shared_ptr<board> board_;
};

class is_within_board : public guard<is_within_board>
{
public:
    using guard::guard;

    bool operator()(const button_clicked&) const {
        //return board_->is_within_board(get_pos(button));
        return true;
    }
};

class is_neighbor : public guard<is_neighbor>
{
public:
    using guard::guard;

    bool operator()(const button_clicked&) const {
        //return board_->is_neighbor(get_pos(button));
        return true;
    }
};

class is_same_item : public guard<is_same_item>
{
public:
    using guard::guard;

    bool operator()(const button_clicked&) const {
        //return board_->is_same_selected(get_pos(button));
        return true;
    }
};

class is_same_color : public guard<is_same_color>
{
public:
    using guard::guard;

    bool operator()(const button_clicked&) const {
        //return board_->is_same_color(get_pos(button));
        return true;
    }
};

class is_swap_items_winning : public guard<is_swap_items_winning>
{
public:
    using guard::guard;

    template<typename Event>
    bool operator()(const Event&) const {
        //return board_->is_swap_winning();
        return true;
    }
};

class is_game_timeout : public guard<is_game_timeout>
{
public:
    using guard::guard;

    bool operator()(const time_tick&) const {
        //return time_ticks_ >= game_time_in_sec_;
        return true;
    }
};

template<int Key>
class is_key : public guard<is_key<Key>>
{
public:
    BOOST_DI_CTOR(is_key) { }

    bool operator()(const key_pressed& event) const {
        return event.key == Key;
    }
};

} // namespace game

#endif

