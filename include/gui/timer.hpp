#ifndef TIMER_908J5PD
#define TIMER_908J5PD

#include <SDL.h>
#include <boost/function.hpp>
#include <boost/di/ctor.hpp>
#include "controller.hpp"
#include "iclient.hpp"

namespace game {
namespace gui {

class timer : public iclient
{
    typedef boost::function<Uint32(Uint32)> callback_t;
    const Uint32 TICK_IN_MILLISECONDS = 1000;

public:
    BOOST_DI_CTOR(explicit timer
        , boost::shared_ptr<controller_t>
    );

    virtual void run() override;

private:
    static Uint32 do_callback(Uint32, void*);
    Uint32 callback(Uint32);

    boost::shared_ptr<controller_t> controller_;
    callback_t callback_;
};

} // namespace gui
} // namespace game

#endif

