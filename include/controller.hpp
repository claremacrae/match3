#ifndef CONTROLLER_AMV06IFP
#define CONTROLLER_AMV06IFP

#include <boost/shared_ptr.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "detail/position.hpp"
#include "events.hpp"
#include "board.hpp"
#include "iviewer.hpp"

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace game {

class game_time_in_sec { };

namespace flags {
class game_over { };
} // namespace flags

class controller : public msm::front::state_machine_def<controller>
{
    struct idle : public msm::front::state<> { };
    struct wait_for_first_item : public msm::front::state<> { };
    struct wait_for_second_item: public msm::front::state<> { };
    struct wait_for_client : public msm::front::state<> { };
    struct let_swap_items : public msm::front::state<> { };
    struct try_swap_items : public msm::front::state<> { };
    struct board_scrolling : public msm::front::state<> { };
    struct game_over : public msm::front::state<>
    {
        typedef boost::mpl::vector1<flags::game_over> flag_list;
    };

    void init_board(const msm::front::none&);
    void select_item(const item_selected&);
    void unselect_item(const item_selected&);
    void swap_items(const msm::front::none&);
    void revert_swap_items(const msm::front::none&);
    void show_matches(const msm::front::none&);
    void scroll_board(const msm::front::none&);
    void show_time(const time_tick&);

    template<typename Event>
    void finish_game(const Event&) {
        viewer_->quit();
    }

    bool is_within_board(const item_selected&);
    bool is_neighbor(const item_selected&);
    bool is_correct_item(const item_selected&);
    bool is_the_same_item(const item_selected&);
    bool is_swap_items_correct(const msm::front::none&);
    bool is_swap_items_incorrect(const msm::front::none&);
    bool is_game_timeout(const time_tick&);
    bool is_not_game_timeout(const time_tick&);

public:
    BOOST_DI_CTOR(controller
        , boost::shared_ptr<board>
        , boost::shared_ptr<iviewer>
        , boost::di::named<int, game_time_in_sec>
    );

    typedef mpl::vector<idle, wait_for_client> initial_state;

    typedef mpl::vector<
         //    Start                , Event            , Target                  , Action                          , Guard
        a_row< idle                 , msm::front::none , wait_for_first_item     , &controller::init_board                                                  >
      ,   row< wait_for_first_item  , item_selected    , wait_for_second_item    , &controller::select_item        , &controller::is_within_board           >
      ,   row< wait_for_second_item , item_selected    , wait_for_first_item     , &controller::unselect_item      , &controller::is_the_same_item          >
      ,   row< wait_for_second_item , item_selected    , let_swap_items          , &controller::select_item        , &controller::is_correct_item           >
      , a_row< let_swap_items       , msm::front::none , try_swap_items          , &controller::swap_items                                                  >
      ,   row< try_swap_items       , msm::front::none , wait_for_first_item     , &controller::revert_swap_items  , &controller::is_swap_items_incorrect   >
      ,   row< try_swap_items       , msm::front::none , board_scrolling         , &controller::show_matches       , &controller::is_swap_items_correct     >
      , a_row< board_scrolling      , msm::front::none , wait_for_first_item     , &controller::scroll_board                                                >

      ,   row< wait_for_client      , time_tick        , game_over               , &controller::finish_game        , &controller::is_game_timeout           >
      ,   row< wait_for_client      , time_tick        , wait_for_client         , &controller::show_time          , &controller::is_not_game_timeout       >
      , a_row< wait_for_client      , key_pressed      , game_over               , &controller::finish_game                                                 >
      , a_row< wait_for_client      , window_close     , game_over               , &controller::finish_game                                                 >

    > transition_table;

    template<class T, class Event>
    void no_transition(const Event&, T&, int) { }

private:
    void show_board();

    boost::shared_ptr<board> board_;
    boost::shared_ptr<iviewer> viewer_;
    int game_time_in_sec_ = 0;
    int time_ticks_ = 0;
};

typedef msm::back::state_machine<controller> controller_t;

} // namespace game

#endif

