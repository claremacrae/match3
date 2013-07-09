#ifndef TIMER_908J5PD
#define TIMER_908J5PD

#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "controller.hpp"
#include "iclient.hpp"

namespace game {
namespace gui {

class game_time_in_sec { };

class timer : public iclient
{
public:
    BOOST_DI_CTOR(explicit timer
        , boost::shared_ptr<controller_t>
        , boost::di::named<int, game_time_in_sec>
    );

    virtual void run() override;

private:
    boost::shared_ptr<controller_t> controller_;
    int time_in_sec_;
};

} // namespace gui
} // namespace game

#endif

