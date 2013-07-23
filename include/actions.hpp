#ifndef ACTIONS_QIAZ45F2
#define ACTIONS_QIAZ45F2

#include <boost/lexical_cast.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <SDL.h>
#include "events.hpp"
#include "guards.hpp"

namespace euml = boost::msm::front::euml;

namespace game {

template<typename FSM>
void show_board(FSM& fsm) {
    fsm.viewer_->clear_board();
    for (int y = 0; y < fsm.board_->get_rows(); y++) {
        for (int x = 0; x < fsm.board_->get_cols(); x++) {
            detail::position pos(x, y);
            fsm.viewer_->show_grid(pos, fsm.board_->get_grid_color(pos));
        }
    }
    fsm.viewer_->render();
}

class init_board : public euml::euml_action<init_board>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->init_with_randoms();
        show_board(fsm);
    }
};

class select_item : public euml::euml_action<select_item>
{
public:
    template<class FSM, class SourceState, class TargetState>
    void operator()(const button_clicked& button, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->select(fsm.get_pos(button));
        fsm.viewer_->select_item(fsm.get_pos(button));
        fsm.viewer_->render();
    }
};

class unselect_all : public euml::euml_action<unselect_all>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->unselect_all();
        show_board(fsm);
    }
};

class swap_items : public euml::euml_action<swap_items>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->swap();
        show_board(fsm);
    }
};

class revert_swap_items : public euml::euml_action<revert_swap_items>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        SDL_Delay(100);
        fsm.board_->swap(); // just swap again
    }
};

class show_matches : public euml::euml_action<show_matches>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        for (const auto& pos : fsm.board_->matches()) {
            fsm.viewer_->show_match(pos);
        }
        fsm.viewer_->render();
        SDL_Delay(300);
    }
};

class scroll_board : public euml::euml_action<scroll_board>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.board_->scroll_down();
        show_board(fsm);
    }
};

class show_time : public euml::euml_action<show_time>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.viewer_->show_time(
            boost::lexical_cast<std::string>(fsm.game_time_in_sec_ - fsm.time_ticks_) + " s"
          , 255
          , 555
          , {0, 0, 0, 0}
          , 32
        );
        fsm.time_ticks_++;
        fsm.viewer_->render();
    }
};

template<int Value>
class add_points : public euml::euml_action<add_points<Value>>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        std::size_t size = fsm.board_->matches().size();
        while (size--) {
            fsm.points += Value;
        }
    }
};

template<int Value>
class sub_points : public euml::euml_action<add_points<Value>>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.points -= Value;
    }
};

class show_points : public euml::euml_action<show_points>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        std::string points = boost::lexical_cast<std::string>(fsm.points);
        fsm.viewer_->show_points(
            boost::lexical_cast<std::string>(fsm.points)
          , 105 - (12 * (points.length() - 1))
          , 435
          , {0, 0, 0, 0}
          , 40
        );
        fsm.viewer_->render();
    }
};

class finish_game : public euml::euml_action<finish_game>
{
public:
    template<class Event, class FSM, class SourceState, class TargetState>
    void operator()(const Event&, FSM& fsm, SourceState&, TargetState&) {
        fsm.viewer_->quit();
    }
};

} // namespace game

#endif

