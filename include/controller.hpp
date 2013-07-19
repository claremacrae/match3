#ifndef CONTROLLER_AMV06IFP
#define CONTROLLER_AMV06IFP

#include <boost/shared_ptr.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "detail/position.hpp"
#include "board.hpp"
#include "iviewer.hpp"
#include "events.hpp"
#include "actions.hpp"
#include "guards.hpp"

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace game {

class game_time_in_sec { };

namespace flags {
class game_over { };
} // namespace flags

class controller : public msm::front::state_machine_def<controller>
{
    template<typename T>
    struct state
        : msm::front::state<>
        , msm::front::euml::euml_state<T>
    { };

    struct idle : state<idle> { };
    struct wait_for_first_item : state<wait_for_first_item> { };
    struct wait_for_second_item: state<wait_for_second_item> { };
    struct wait_for_client : state<wait_for_client> { };
    struct let_swap_items : state<let_swap_items> { };
    struct try_swap_items : state<try_swap_items> { };
    struct board_scrolling : state<board_scrolling> { };
    struct game_over : state<game_over>
    {
        typedef boost::mpl::vector1<flags::game_over> flag_list;
    };

public:
    BOOST_DI_CTOR(controller
        , boost::shared_ptr<board>
        , boost::shared_ptr<iviewer>
        , boost::di::named<int, game_time_in_sec>
    );

    typedef mpl::vector<idle, wait_for_client> initial_state;

    BOOST_MSM_EUML_DECLARE_TRANSITION_TABLE((
   // +--------------------------------------------------------------------------------------------------------------------------------------------+
        idle()                    [anonymous()] / init_board()                                                          == wait_for_first_item()
      , wait_for_first_item()   + item_selected()[is_within_board()] / select_item()                                    == wait_for_second_item()
      , wait_for_second_item()  + item_selected()[is_the_same_item()] / unselect_item()                                 == wait_for_first_item()
      , wait_for_second_item()  + item_selected()[is_within_board() and is_neighbor()] / (select_item(), swap_items())  == try_swap_items()
      , try_swap_items()          [is_swap_items_correct()] / (show_matches(), scroll_board())                          == wait_for_first_item()
      , try_swap_items()          [not is_swap_items_correct()] / revert_swap_items()                                   == wait_for_first_item()
   // +--------------------------------------------------------------------------------------------------------------------------------------------+
      , wait_for_client()       + time_tick()[is_game_timeout()] / finish_game()                                        == game_over()
      , wait_for_client()       + time_tick()[not is_game_timeout()] / show_time()
      , wait_for_client()       + key_pressed()[is_key<SDLK_ESCAPE>()] / finish_game()                                  == game_over()
      , wait_for_client()       + window_close() / finish_game()                                                        == game_over()
   // +--------------------------------------------------------------------------------------------------------------------------------------------+
    ), transition_table);

    template<class T, class Event>
    void no_transition(const Event&, T&, int) { }

//private:
public: /*FIXME: temporary workaround*/
    boost::shared_ptr<board> board_;
    boost::shared_ptr<iviewer> viewer_;
    int game_time_in_sec_ = 0;
    int time_ticks_ = 0;
};

typedef msm::back::state_machine<controller> controller_t;

} // namespace game

#endif

