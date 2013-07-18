#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include "events.hpp"

namespace game {

class always_true
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    bool operator()(const Event&, FSM&, SourceState&, TargetState&) {
        return true;
    }
};

class is_within_board
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_within_board(event.pos);
    }
};

class is_neighbor
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_neighbor(event.pos);
    }
};

class is_correct_item
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_within_board(event.pos) and fsm.board_->is_neighbor(event.pos);
    }
};

class is_the_same_item
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_same_selected(event.pos);
    }
};

class is_swap_items_correct
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    bool operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_swap_winning();
    }
};

class is_swap_items_incorrect
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    bool operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        return !fsm.board_->is_swap_winning();
    }
};

class is_game_timeout
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const time_tick&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.time_ticks_ >= fsm.game_time_in_sec_;
    }
};

class is_not_game_timeout
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const time_tick&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.time_ticks_ < fsm.game_time_in_sec_;
    }
};

} // namespace game

#endif

