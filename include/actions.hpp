#ifndef ACTIONS_QIAZ45F2
#define ACTIONS_QIAZ45F2

#include <boost/lexical_cast.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <SDL.h>
#include "events.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

template<typename FSM>
void show_board(FSM& fsm) {
    fsm.viewer_->set_background();
    for (int y = 0; y < fsm.board_->get_rows(); y++) {
        for (int x = 0; x < fsm.board_->get_cols(); x++) {
            detail::position pos(x, y);
            fsm.viewer_->show_grid(pos, fsm.board_->get_grid_color(pos));
        }
    }
    fsm.viewer_->render();
}

static class init_board_ : public euml::euml_action<init_board_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->init_with_randoms();
        show_board(fsm);
    }
} init_board;

static class select_item_ : public euml::euml_action<select_item_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->select(event.pos);
        fsm.viewer_->select_item(event.pos);
        fsm.viewer_->render();
    }
} select_item;

static class unselect_item_ : public euml::euml_action<unselect_item_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const item_selected&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->unselect_all();
        show_board(fsm);
    }
} unselect_item;

static class swap_items_ : public euml::euml_action<swap_items_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->swap();
        show_board(fsm);
    }
} swap_items;

static class revert_swap_items_ : public euml::euml_action<revert_swap_items_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        SDL_Delay(100);
        fsm.board_->swap(); // just swap again
        fsm.board_->unselect_all();
        show_board(fsm);
    }
} revert_swap_items;

static class show_matches_ : public euml::euml_action<show_matches_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        for (auto& pos : fsm.board_->matches()) {
            fsm.viewer_->show_match(pos);
        }
        fsm.board_->unselect_all();
        fsm.viewer_->render();
        SDL_Delay(300);
    }
} show_matches;

static class scroll_board_ : public euml::euml_action<scroll_board_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->scroll_down();
        show_board(fsm);
    }
} scroll_board;

static class show_time_ : public euml::euml_action<show_time_>
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const time_tick&, FSM& fsm, SourceState&, TargetState&) {
        fsm.viewer_->show_text(
            boost::lexical_cast<std::string>(fsm.game_time_in_sec_ - fsm.time_ticks_)
          , 50
          , 50
        );
        fsm.time_ticks_++;
        fsm.viewer_->render();
    }
} show_time;

static class finish_game_ : public euml::euml_action<finish_game_>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.viewer_->quit();
    }
} finish_game;

} // namespace game

#endif

