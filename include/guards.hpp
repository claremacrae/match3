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
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const button_clicked& button, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_within_board(fsm.get_pos(button));
    }
};

class is_neighbor : public euml::euml_action<is_neighbor>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const button_clicked& button, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_neighbor(fsm.get_pos(button));
    }
};

class is_same_item : public euml::euml_action<is_same_item>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const button_clicked& button, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_same_selected(fsm.get_pos(button));
    }
};

class is_same_color : public euml::euml_action<is_same_color>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const button_clicked& button, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_same_color(fsm.get_pos(button));
    }
};

class is_swap_items_winning : public euml::euml_action<is_swap_items_winning>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    bool operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_swap_winning();
    }
};

class is_game_timeout : public euml::euml_action<is_game_timeout>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const time_tick&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.time_ticks_ >= fsm.game_time_in_sec_;
    }
};

template<int Key>
class is_key : public euml::euml_action<is_key<Key>>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const key_pressed& event, FSM&, SourceState&, TargetState&) {
        return event.key == Key;
    }
};

} // namespace game

#endif

