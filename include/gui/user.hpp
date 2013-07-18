#ifndef USER_ZJZFAXBM
#define USER_ZJZFAXBM

#include <boost/di/ctor.hpp>
#include "controller.hpp"
#include "iclient.hpp"
#include "iviewer.hpp"

namespace game {
namespace gui {

class user: public iclient
{
public:
    BOOST_DI_CTOR(explicit user, boost::shared_ptr<controller_t>, boost::shared_ptr<iviewer>);
    virtual void run() override;

private:
    boost::shared_ptr<controller_t> controller_;
    boost::shared_ptr<iviewer> v_;
};

} // namespace gui
} // namespace game

#endif

