#ifndef APP_F6TO27D7
#define APP_F6TO27D7

#include <boost/shared_ptr.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "controller.hpp"
#include "iclient.hpp"

namespace game {

class user { };
class timer { };

class app
{
public:
    BOOST_DI_CTOR(app
        , boost::shared_ptr<controller_t>
        , boost::di::named<boost::shared_ptr<iclient>, user>
        , boost::di::named<boost::shared_ptr<iclient>, timer>
    );

    void play();

private:
    boost::shared_ptr<controller_t> controller_;
    boost::shared_ptr<iclient> user_;
    boost::shared_ptr<iclient> timer_;
};

} // namespace game

#endif

