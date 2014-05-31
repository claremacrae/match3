#ifndef USER_ZJZFAXBM
#define USER_ZJZFAXBM

#include <boost/di/ctor.hpp>
#include "controller.hpp"
#include "iclient.hpp"
#include "iviewer.hpp"

namespace match3 {
namespace gui {

class user : public iclient
{
public:
    BOOST_DI_CTOR(explicit user, std::shared_ptr<controller_t>);
    virtual void run() override;

private:
    std::shared_ptr<controller_t> controller_;
};

} // namespace gui
} // namespace match3

#endif

