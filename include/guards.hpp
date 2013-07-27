#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include <boost/msm/front/euml/euml.hpp>
#include "detail/position.hpp"
#include "events.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

class is_within_board : public euml::euml_action<is_within_board>
{
public:
    bool operator()(const button_clicked&) {
        //return fsm.board_->is_within_board(fsm.get_pos(button));
        return true;
    }
};

class is_neighbor : public euml::euml_action<is_neighbor>
{
public:
    bool operator()(const button_clicked&) {
        //return fsm.board_->is_neighbor(fsm.get_pos(button));
        return true;
    }
};

class is_same_item : public euml::euml_action<is_same_item>
{
public:
    bool operator()(const button_clicked&) {
        //return fsm.board_->is_same_selected(fsm.get_pos(button));
        return true;
    }
};

class is_same_color : public euml::euml_action<is_same_color>
{
public:
    bool operator()(const button_clicked&) {
        //return fsm.board_->is_same_color(fsm.get_pos(button));
        return true;
    }
};

class is_swap_items_winning : public euml::euml_action<is_swap_items_winning>
{
public:
    template<typename Event>
    bool operator()(const Event&) {
        //return fsm.board_->is_swap_winning();
        return true;
    }
};

class is_game_timeout : public euml::euml_action<is_game_timeout>
{
public:
    bool operator()(const time_tick&) {
        //return fsm.time_ticks_ >= fsm.game_time_in_sec_;
        return true;
    }
};

template<int Key>
class is_key : public euml::euml_action<is_key<Key>>
{
public:
    bool operator()(const key_pressed& event) {
        return event.key == Key;
    }
};

} // namespace game

#endif

