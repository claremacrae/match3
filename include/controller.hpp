#ifndef CONTROLLER_AMV06IFP
#define CONTROLLER_AMV06IFP

#include <boost/shared_ptr.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "sdl/msm.hpp"
#include "detail/position.hpp"
#include "events_traits.hpp"
#include "board.hpp"
#include "iviewer.hpp"
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
    BOOST_DI_CTOR(controller
        , boost::shared_ptr<board> b
        , boost::shared_ptr<iviewer> v
        , boost::di::named<int, _S("game time in seconds")> t
        , boost::di::named<int, _S("grid offset")> g
        , boost::di::named<int, _S("grids offset x")> x
        , boost::di::named<int, _S("grids offset y")> y
    ) : board_(b)
      , viewer_(v)
      , game_time_in_sec_(t)
      , grid_offset_(g)
      , grids_offset_x_(x)
      , grids_offset_y_(y)
    { };

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

    //FIXME: temporary workaround
    detail::position get_pos(const button_clicked& button) {
        return detail::position(
            (button.x - grids_offset_x_) / grid_offset_
          , (button.y - grids_offset_y_) / grid_offset_
        );
    }

//private:
public: //FIXME: temporary workaround
    boost::shared_ptr<board> board_;
    boost::shared_ptr<iviewer> viewer_;
    int game_time_in_sec_ = 0;
    int time_ticks_ = 0;
    int grid_offset_ = 0;
    int grids_offset_x_ = 0;
    int grids_offset_y_ = 0;
    int points = 0;
};

typedef sdl::msm<controller, events_traits> controller_t;

} // namespace game

#endif

