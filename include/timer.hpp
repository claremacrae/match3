#ifndef TIMER_908J5PD
#define TIMER_908J5PD

#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "controller.hpp"

namespace game {

class game_time_in_sec { };

class timer
{
public:
    BOOST_DI_CTOR(explicit timer
        , const boost::shared_ptr<controller_t>&
        , boost::di::named<int, game_time_in_sec>
    );

    void run();

private:
    boost::shared_ptr<controller_t> controller_;
    int time_in_sec_;
};

} // namespace game

#endif

