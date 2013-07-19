#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include <boost/msm/front/euml/euml.hpp>
#include "events.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

static class is_within_board_ : public euml::euml_action<is_within_board_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_within_board(event.pos);
    }
} is_within_board;

static class is_neighbor_ : public euml::euml_action<is_neighbor_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_neighbor(event.pos);
    }
} is_neighbor;

static class is_the_same_item_ : public euml::euml_action<is_the_same_item_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_same_selected(event.pos);
    }
} is_the_same_item;

static class is_swap_items_correct_ : public euml::euml_action<is_swap_items_correct_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    bool operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.board_->is_swap_winning();
    }
} is_swap_items_correct;

static class is_game_timeout_ : public euml::euml_action<is_game_timeout_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    bool operator()(const time_tick&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.time_ticks_ >= fsm.game_time_in_sec_;
    }
} is_game_timeout;

} // namespace game

#endif

