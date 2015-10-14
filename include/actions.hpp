#ifndef ACTIONS_QIAZ45F2
#define ACTIONS_QIAZ45F2

#include <memory>
#include <boost/msm/front/euml/euml.hpp>
#include <SDL.h>
#include "sdl/timer.hpp"
#include "position.hpp"
#include "time_ticks.hpp"
#include "ipoints.hpp"
#include "iboard.hpp"
#include "iviewer.hpp"
#include "events.hpp"

namespace match3 {

template<typename T>
class action : public boost::msm::front::euml::euml_action<T>
{
public:
    action() { }

    action(std::shared_ptr<iboard> b
         , std::shared_ptr<iviewer> v)
        : board_(b), viewer_(v)
    { }

protected:
    void show_board(sdl::milliseconds_t delay = 0, bool render = false) {
        viewer_->clear_board();

        for (const auto& pos : *board_) {
            viewer_->show_grid(pos, board_->get_grid_color(pos));
            if (render) {
                viewer_->render();
            }
        }

        viewer_->render(delay);
    }

    std::shared_ptr<iboard> board_;
    std::shared_ptr<iviewer> viewer_;
};

class init_board : public action<init_board>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->init_with_randoms();
        show_board(0, true);
    }
};

class select_item : public action<select_item>
{
public:
    using action::action;

    void operator()(const button_clicked& button) {
        board_->select(button.pos);
        viewer_->select_item(button.pos);
        viewer_->render();
    }
};

class unselect_all : public action<unselect_all>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->unselect_all();
        show_board();
    }
};

class swap_items : public action<swap_items>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->swap();
        show_board(100);
    }
};

class revert_swap_items : public action<revert_swap_items>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->swap(); // just swap again
    }
};

class show_matches : public action<show_matches>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        for (const auto& pos : board_->matches()) {
            viewer_->show_match(pos);
        }
        viewer_->render(300);
    }
};

class scroll_board : public action<scroll_board>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        for (const auto& pos : board_->scroll_down()) {
            board_->select(pos);
        }

        show_board(100);

        for (const auto& pos : board_->new_randoms()) {
            viewer_->scroll_grid(pos, board_->get_grid_color(pos));
            board_->select(pos);
        }

        viewer_->render(100);
        show_board();
    }
};

class show_time : public action<show_time>
{
public:
    show_time() { }

    BOOST_DI_INJECT(show_time
                  , std::shared_ptr<iboard> b
                  , std::shared_ptr<iviewer> v
                  , std::shared_ptr<time_ticks> t
                  , (named = "game_time_in_seconds"_s) time_ticks s)
        : action(b, v), time_ticks_(t), game_time_in_sec_(s)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_time(game_time_in_sec_ - *time_ticks_);
        (*time_ticks_)++;
        viewer_->render();
    }

private:
    std::shared_ptr<time_ticks> time_ticks_;
    time_ticks game_time_in_sec_ = 0;
};

template<int Value>
class add_points : public action<add_points<Value>>
{
    typedef action<add_points<Value>> action_t;

public:
    add_points() { }

    add_points(std::shared_ptr<iboard> b
             , std::shared_ptr<ipoints> p)
        : action_t(b, std::shared_ptr<iviewer>()), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        std::size_t size = action_t::board_->matches().size();
        while (size--) {
            points_->add(Value);
        }
    }

private:
    std::shared_ptr<ipoints> points_;
};

template<int Value>
class sub_points : public action<sub_points<Value>>
{
    typedef action<sub_points<Value>> action_t;

public:
    sub_points() { }

    sub_points(std::shared_ptr<ipoints> p)
        : points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        points_->sub(Value);
    }

private:
    std::shared_ptr<ipoints> points_;
};

class show_points : public action<show_points>
{
public:
    show_points() { }

    show_points(std::shared_ptr<iboard> b
              , std::shared_ptr<iviewer> v
              , std::shared_ptr<ipoints> p)
        : action(b, v), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_points(*points_);
        viewer_->render();
    }

private:
    std::shared_ptr<ipoints> points_;
};

class show_results : public action<show_results>
{
public:
    show_results() { }

    show_results(std::shared_ptr<iboard> b
               , std::shared_ptr<iviewer> v
               , std::shared_ptr<ipoints> p)
        : action(b, v), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_results(*points_);
        viewer_->render();
    }

private:
    std::shared_ptr<ipoints> points_;
};

class fade_screen : public action<fade_screen>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        viewer_->fade_screen(10);
    }
};

class finish_game : public action<finish_game>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        viewer_->quit();
    }
};

} // namespace match3

#endif

