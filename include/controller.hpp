#ifndef CONTROLLER_AMV06IFP
#define CONTROLLER_AMV06IFP

#include <boost/shared_ptr.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include "sdl/msm.hpp"
#include "events.hpp"
#include "actions.hpp"
#include "guards.hpp"

namespace mpl   = boost::mpl;
namespace front = boost::msm::front;
namespace euml  = boost::msm::front::euml;

namespace game {

class controller : public front::state_machine_def<controller>
{
    struct idle                 : front::state<>, euml::euml_state<idle> { };
    struct wait_for_first_item  : front::state<>, euml::euml_state<wait_for_first_item> { };
    struct wait_for_second_item : front::state<>, euml::euml_state<wait_for_second_item> { };
    struct wait_for_client      : front::state<>, euml::euml_state<wait_for_client> { };
    struct let_swap_items       : front::state<>, euml::euml_state<let_swap_items> { };
    struct try_swap_items       : front::state<>, euml::euml_state<try_swap_items> { };
    struct board_scrolling      : front::state<>, euml::euml_state<board_scrolling> { };
    struct game_over            : front::state<>, euml::euml_state<game_over>
    {
        typedef mpl::vector1<flag_game_over> flag_list;
    };
    struct wait_for_any_key     : front::interrupt_state<key_pressed>, euml::euml_state<wait_for_any_key> { };

public:
    typedef mpl::vector<idle, wait_for_client> initial_state;

    BOOST_MSM_EUML_DECLARE_TRANSITION_TABLE((
   // +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
        wait_for_first_item()  == idle()                   [anonymous()] / (init_board(), show_time(), show_points())
      , wait_for_second_item() == wait_for_first_item()  + button_clicked() [is_within_board()] / select_item()
      , wait_for_first_item()  == wait_for_second_item() + button_clicked() [is_same_item()] / unselect_all()
      , try_swap_items()       == wait_for_second_item() + button_clicked() [is_within_board() and not is_same_color() and is_neighbor()] / (select_item(), swap_items())
      , wait_for_first_item()  == try_swap_items()         [is_swap_items_winning()] / (show_matches(), add_points<10>(), show_points(), unselect_all(), scroll_board())
      , wait_for_first_item()  == try_swap_items()         [not is_swap_items_winning()] / (revert_swap_items(), sub_points<5>(), show_points(), unselect_all())
   // +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
      , wait_for_any_key()     == wait_for_client()      + time_tick() [is_game_timeout()] / show_results()
      ,                           wait_for_client()      + time_tick() [not is_game_timeout()] / show_time()
      , wait_for_any_key()     == wait_for_client()      + key_pressed() [is_key<SDLK_ESCAPE>()] / show_results()
      , wait_for_any_key()     == wait_for_client()      + window_close() / show_results()
      , game_over()            == wait_for_any_key()     + key_pressed() / finish_game()
   // +------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    ), transition_table)
};

typedef sdl::msm<controller> controller_t;

} // namespace game

#endif

