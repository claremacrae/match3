#ifndef GUARDS_KWSYEU3M
#define GUARDS_KWSYEU3M

#include <memory>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/di/named.hpp>
#include "time_ticks.hpp"
#include "iboard.hpp"
#include "events.hpp"

namespace mpl  = boost::mpl;
namespace euml = boost::msm::front::euml;

namespace match3 {

using is_within_board       = euml::bind_guard<euml_call(&iboard::is_within_board), mpl::_1>;
using is_neighbor           = euml::bind_guard<euml_call(&iboard::is_neighbor), mpl::_1>;
using is_same_item          = euml::bind_guard<euml_call(&iboard::is_same_selected), mpl::_1>;
using is_same_color         = euml::bind_guard<euml_call(&iboard::is_same_color), mpl::_1>;
using is_swap_items_winning = euml::bind_guard<euml_call(&iboard::is_swap_winning)>;
using are_selected          = euml::bind_guard<euml_call(&iboard::are_selected)>;

class is_game_timeout : public euml::euml_action<is_game_timeout>
{
public:
    is_game_timeout() { }

    is_game_timeout(std::shared_ptr<time_ticks> t
                  , boost::di::named<time_ticks, _S("game time in seconds")> s)
        : time_ticks_(t), game_time_in_sec_(s)
    { }

    bool operator()(const time_tick&) const {
        return *time_ticks_ >= game_time_in_sec_;
    }

private:
    std::shared_ptr<time_ticks> time_ticks_;
    time_ticks game_time_in_sec_ = 0;
};

template<int Key>
class is_key : public euml::euml_action<is_key<Key>>
{
public:
    bool operator()(const key_pressed& event) const {
        return event.key == Key;
    }
};

} // namespace match3

#endif

