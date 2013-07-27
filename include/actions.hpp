#ifndef ACTIONS_QIAZ45F2
#define ACTIONS_QIAZ45F2

#include <boost/shared_ptr.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <SDL.h>
#include "detail/position.hpp"
#include "board.hpp"
#include "iviewer.hpp"
#include "events.hpp"

namespace game {

template<typename T>
class action : public boost::msm::front::euml::euml_action<T>
{
public:
    BOOST_DI_CTOR(action
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>()
        , boost::shared_ptr<iviewer> v = boost::shared_ptr<iviewer>())
        : board_(b), viewer_(v)
    { }

protected:
    void show_board() {
        viewer_->clear_board();
        for (int y = 0; y < board_->get_rows(); y++) {
            for (int x = 0; x < board_->get_cols(); x++) {
                detail::position pos(x, y);
                viewer_->show_grid(pos, board_->get_grid_color(pos));
            }
        }
        viewer_->render();
    }

    boost::shared_ptr<board> board_;
    boost::shared_ptr<iviewer> viewer_;
};

class init_board : public action<init_board>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->init_with_randoms();
        show_board();
    }
};

class select_item : public action<select_item>
{
public:
    using action::action;

    void operator()(const button_clicked& button) {
        board_->select(get_pos(button));
        viewer_->select_item(get_pos(button));
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
        show_board();
    }
};

class revert_swap_items : public action<revert_swap_items>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        SDL_Delay(100);
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
        viewer_->render();
        SDL_Delay(300);
    }
};

class scroll_board : public action<scroll_board>
{
public:
    using action::action;

    template<class Event>
    void operator()(const Event&) {
        board_->scroll_down();
        show_board();
    }
};

class show_time : public action<show_time>
{
public:
    BOOST_DI_CTOR(show_time
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>()
        , boost::shared_ptr<iviewer> v = boost::shared_ptr<iviewer>()
        , boost::shared_ptr<int> t = boost::shared_ptr<int>()
        , boost::di::named<int, _S("game time in seconds")> s = 0)
        : action(0, b, v), time_ticks_(t), game_time_in_sec_(s)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_time(game_time_in_sec_ - *time_ticks_);
        (*time_ticks_)++;
        viewer_->render();
    }

private:
    int game_time_in_sec_ = 0;
    boost::shared_ptr<int> time_ticks_;
};

template<int Value>
class add_points : public action<add_points<Value>>
{
    using action<add_points<Value>>::board_;

public:
    BOOST_DI_CTOR(add_points
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>()
        , boost::shared_ptr<int> p = boost::shared_ptr<int>())
        : action<add_points<Value>>(0, b), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        std::size_t size = board_->matches().size();
        while (size--) {
            *points_ += Value;
        }
    }

private:
    boost::shared_ptr<int> points_;
};

template<int Value>
class sub_points : public action<sub_points<Value>>
{
public:
    BOOST_DI_CTOR(sub_points
        , int = 0 /*dummy*/
        , boost::shared_ptr<int> p = boost::shared_ptr<int>())
        : points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        *points_ -= Value;
    }

private:
    boost::shared_ptr<int> points_;
};

class show_points : public action<show_points>
{
public:
    BOOST_DI_CTOR(show_points
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>()
        , boost::shared_ptr<iviewer> v = boost::shared_ptr<iviewer>()
        , boost::shared_ptr<int> p = boost::shared_ptr<int>())
        : action(0, b, v), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_points(*points_);
        viewer_->render();
    }

private:
    boost::shared_ptr<int> points_;
};

class show_results : public action<show_results>
{
public:
    BOOST_DI_CTOR(show_results
        , int = 0 /*dummy*/
        , boost::shared_ptr<board> b = boost::shared_ptr<board>()
        , boost::shared_ptr<iviewer> v = boost::shared_ptr<iviewer>()
        , boost::shared_ptr<int> p = boost::shared_ptr<int>())
        : action(0, b, v), points_(p)
    { }

    template<class Event>
    void operator()(const Event&) {
        viewer_->show_results(*points_);
        viewer_->render();
    }

private:
    boost::shared_ptr<int> points_;
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

} // namespace game

#endif

