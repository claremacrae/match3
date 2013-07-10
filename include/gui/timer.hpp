#ifndef TIMER_908J5PD
#define TIMER_908J5PD

#include <SDL.h>
#include <boost/di/ctor.hpp>
#include "controller.hpp"
#include "iclient.hpp"

namespace game {
namespace gui {

class timer : public iclient
{
    const Uint32 TICK_IN_MILLISECONDS = 1000;

public:
    BOOST_DI_CTOR(explicit timer
        , boost::shared_ptr<controller_t>
    );

    virtual void run() override;

private:
    boost::shared_ptr<controller_t> controller_;
};

} // namespace gui
} // namespace game

#endif

