#ifndef TIME_908J5PD
#define TIME_908J5PD

#include <boost/di/ctor.hpp>
#include "sdl/timer.hpp"
#include "controller.hpp"
#include "iclient.hpp"

namespace game {
namespace gui {

class time : public iclient
{
    const sdl::milliseconds_t TICK_EVERY_SECOND_IN_MILLISECONDS = 1000;

public:
    BOOST_DI_CTOR(explicit time
        , boost::shared_ptr<controller_t>
    );

    virtual void run() override;

private:
    boost::shared_ptr<controller_t> controller_;
    boost::shared_ptr<sdl::timer> timer_;
};

} // namespace gui
} // namespace game

#endif

