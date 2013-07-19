#ifndef APP_F6TO27D7
#define APP_F6TO27D7

#include <boost/shared_ptr.hpp>
#include "controller.hpp"
#include "iclient.hpp"

namespace game {

class app
{
public:
    template<typename... TClients>
    explicit app(boost::shared_ptr<controller_t> c, TClients&&... cl)
        : controller_(c), clients_{std::forward<TClients>(cl)...}
    { };

    void play();

private:
    boost::shared_ptr<controller_t> controller_;
    std::vector<boost::shared_ptr<iclient>> clients_;
};

} // namespace game

#endif

