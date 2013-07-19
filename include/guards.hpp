#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include <boost/msm/front/euml/euml.hpp>
#include "events.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

class is_within_board : public euml::euml_action<is_within_board>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_within_board(event.pos);
    }
};

class is_neighbor : public euml::euml_action<is_neighbor>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_neighbor(event.pos);
    }
};

class is_the_same_item : public euml::euml_action<is_the_same_item>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_same_selected(event.pos);
    }
};

class is_swap_items_correct : public euml::euml_action<is_swap_items_correct>
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

