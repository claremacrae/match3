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
   // +---------------------------------------------------------------------------------------------------------------------+
        wait_for_first_item()  == idle()                   [anonymous()] / init_board()
      , wait_for_second_item() == wait_for_first_item()  + button_clicked() [is_within_board()] / select_item()
      , wait_for_first_item()  == wait_for_second_item() + button_clicked() [is_same_item()] / unselect_all()
      , try_swap_items()       == wait_for_second_item() + button_clicked() [is_within_board() and
                                                                             not is_same_color() and
                                                                             is_neighbor()] / (select_item(), swap_items())
      , wait_for_first_item()  == try_swap_items()         [is_swap_items_winning()] / (show_matches(), scroll_board())
      , wait_for_first_item()  == try_swap_items()         [not is_swap_items_winning()] / revert_swap_items()
   // +---------------------------------------------------------------------------------------------------------------------+
      , game_over()            == wait_for_client()      + time_tick() [is_game_timeout()] / finish_game()
      ,                           wait_for_client()      + time_tick() [not is_game_timeout()] / show_time()
      , game_over()            == wait_for_client()      + key_pressed() [is_key<SDLK_ESCAPE>()] / finish_game()
      , game_over()            == wait_for_client()      + window_close() / finish_game()
   // +---------------------------------------------------------------------------------------------------------------------+
    ), transition_table);

    template<class T, class Event>
    void no_transition(const Event&, T&, int) { }

    //FIXME: temporary workaround
    detail::position get_pos(const button_clicked& button) {
        return detail::position(
            (button.button.x - grids_offset_x_) / grid_offset_
          , (button.button.y - grids_offset_y_) / grid_offset_
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
};

typedef msm::back::state_machine<controller> controller_t;

} // namespace game

#endif

