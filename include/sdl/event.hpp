#ifndef EVENT_PGQOCBAA
#define EVENT_PGQOCBAA

#include <boost/msm/front/euml/euml.hpp>

namespace game {

typedef boost::msm::front::euml::True_ anonymous;

namespace sdl {

template<typename T, int Id = __COUNTER__>
struct event : boost::msm::front::euml::euml_event<T>
{
    typedef void is_event;
    static const int id = Id;
};

} // namespace sdl
} // namespace game

#endif

