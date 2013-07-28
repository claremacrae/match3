#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <gtest/gtest.h>
#include "sdl/msm.hpp"

namespace mpl   = boost::mpl;
namespace front = boost::msm::front;
namespace euml  = boost::msm::front::euml;

namespace game {
namespace sdl {
namespace test {

struct fake_event
{
    static const int FAKE_ID = 42;
    typedef boost::mpl::int_<FAKE_ID> id;
};

class fake_state_machine_ : public front::state_machine_def<fake_state_machine_>
{
    struct idle : front::state<>, euml::euml_state<idle> { };

public:
    typedef mpl::vector<idle> initial_state;

    BOOST_MSM_EUML_DECLARE_TRANSITION_TABLE((
        idle()  == idle() + fake_event()
    ), transition_table)
};

typedef msm<fake_state_machine_> fake_state_machine;

struct fake_SDL
{
    static int fake_SDL_PushEvent(SDL_Event* event) {
        EXPECT_EQ(event->type, SDL_USEREVENT);
        EXPECT_EQ(event->user.code, fake_event::id::value);
        SDL_PushEvent_calls++;
        return 0;
    }

    static int SDL_PushEvent_calls;
};

int fake_SDL::SDL_PushEvent_calls = 0;

TEST(msm_test, process_event_typed) {
    //given
    msm<fake_state_machine, fake_SDL::fake_SDL_PushEvent> msm_;
    fake_SDL::SDL_PushEvent_calls = 0;

    //when
    msm_.process_event(fake_event());

    //then
    EXPECT_EQ(1, fake_SDL::SDL_PushEvent_calls);
}

} // namespace test
} // namespace sdl
} // namespace game

