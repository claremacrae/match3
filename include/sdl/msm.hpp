#ifndef MSM_KRNOGIYP
#define MSM_KRNOGIYP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <SDL.h>

namespace back = boost::msm::back;
namespace mpl = boost::mpl;

namespace game {
namespace sdl {

template<
    typename M
  , template<typename> class EventsTraits
>
class msm : public back::state_machine<M>
{
    template<typename T>
    struct event
    {
        typedef typename T::Evt type;
    };

    template<typename T>
    using events = typename mpl::transform<T, event<mpl::_1>>::type;

public:
    template<typename... Args>
    msm(Args&&... args)
        : back::state_machine<M>(std::forward<Args>(args)...)
    { }

    template<typename TEvent>
    void process_event(const TEvent& event) {
        SDL_Event sdl_event;
        sdl_event.type = SDL_USEREVENT;
        sdl_event.user.code = EventsTraits<TEvent>::id;
        sdl_event.user.data1 = (void*)&event;
        sdl_event.user.data2 = nullptr;
        SDL_PushEvent(&sdl_event);
    }

    void process_event(const SDL_Event& event) {
        typedef typename back::state_machine<M>::transition_table transition_table;
        for_events<typename events<transition_table>::type>(event);
    }

private:
    template<typename Seq>
    void for_events(const SDL_Event&, typename boost::enable_if<mpl::empty<Seq>>::type* = 0) { }

    template<typename Seq>
    void for_events(const SDL_Event& event, typename boost::disable_if<mpl::empty<Seq>>::type* = 0) {
        typedef typename mpl::front<Seq>::type event_t;
        if (event.user.code == EventsTraits<event_t>::id) {
            back::state_machine<M>::process_event(*static_cast<event_t*>(event.user.data1));
        } else {
            for_events<typename mpl::pop_front<Seq>::type>(event);
        }
    }
};

} // namespace sdl
} // namespace game

#endif

