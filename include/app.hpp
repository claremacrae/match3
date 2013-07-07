#ifndef APP_F6TO27D7
#define APP_F6TO27D7

#include <boost/shared_ptr.hpp>
#include <boost/di/ctor.hpp>
#include "controller.hpp"
#include "timer.hpp"
#include "iclient.hpp"
#include "iviewer.hpp"

namespace game {

class app
{
public:
    BOOST_DI_CTOR(app
        , const boost::shared_ptr<controller_t>&
        , const boost::shared_ptr<iclient>&
        , const boost::shared_ptr<timer>&
    );

    void play();

private:
    boost::shared_ptr<controller_t> controller_;
    boost::shared_ptr<iclient> client_;
    boost::shared_ptr<timer> timer_;
};

} // namespace game

#endif

