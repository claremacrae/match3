#include <boost/mpl/vector.hpp>
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

class fake_state_machine_ : public front::state_machine_def<fake_state_machine_>
{
    struct idle : front::state<>, euml::euml_state<idle> { };

public:
    typedef mpl::vector<idle> initial_state;

    BOOST_MSM_EUML_DECLARE_TRANSITION_TABLE((
        idle()  == idle()
    ), transition_table)
};

typedef msm<fake_state_machine_> fake_state_machine;

TEST(msm_test, process_event) {
    msm<fake_state_machine> msm_;
}

} // namespace test
} // namespace sdl
} // namespace game

