#ifndef CLIENT_ZJZFAXBM
#define CLIENT_ZJZFAXBM

#include <boost/di/ctor.hpp>
#include "iclient.hpp"
#include "controller.hpp"

namespace game {
namespace gui {

class client : public iclient
{
public:
    BOOST_DI_CTOR(explicit client, const boost::shared_ptr<controller_t>&);
    virtual void run() override;

private:
    boost::shared_ptr<controller_t> controller_;
};

} // namespace gui
} // namespace game

#endif

