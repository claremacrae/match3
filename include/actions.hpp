#ifndef ACTIONS_QIAZ45F2
#define ACTIONS_QIAZ45F2

#include <boost/lexical_cast.hpp>
#include <SDL.h>
#include "events.hpp"

namespace msm = boost::msm;

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

class init_board
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->init_with_randoms();
        show_board(fsm);
    }
};

class select_item
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const item_selected& event, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->select(event.pos);
        fsm.viewer_->select_item(event.pos);
        fsm.viewer_->render();
    }
};

class unselect_item
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const item_selected&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->unselect_all();
        show_board(fsm);
    }
};

class swap_items
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const msm::front::none&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->swap();
        show_board(fsm);
    }
};

class revert_swap_items
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const msm::front::none&, FSM& fsm, SourceState&, TargetState&) {
        SDL_Delay(100);
        fsm.board_->swap(); // just swap again
        fsm.board_->unselect_all();
        show_board(fsm);
    }
};

class show_matches
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const msm::front::none&, FSM& fsm, SourceState&, TargetState&) {
        for (auto& pos : fsm.board_->matches()) {
            fsm.viewer_->show_match(pos);
        }
        fsm.board_->unselect_all();
        fsm.viewer_->render();
        SDL_Delay(300);
    }
};

class scroll_board
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const msm::front::none&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->scroll_down();
        show_board(fsm);
    }
};

class show_time
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
};

class finish_game
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.viewer_->quit();
    }
};

} // namespace game

#endif

