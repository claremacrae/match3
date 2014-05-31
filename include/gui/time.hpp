#ifndef TIME_908J5PD
#define TIME_908J5PD

#include <boost/di/ctor.hpp>
#include "sdl/timer.hpp"
#include "controller.hpp"
#include "iclient.hpp"

namespace match3 {
namespace gui {

class time : public iclient
{
    const sdl::milliseconds_t ONE_SECOND_IN_MILLISECONDS = 1000;

public:
    BOOST_DI_CTOR(explicit time
        , std::shared_ptr<controller_t>
    );

    virtual void run() override;

private:
    std::shared_ptr<controller_t> controller_;
    std::shared_ptr<sdl::timer> timer_;
};

} // namespace gui
} // namespace match3

#endif

