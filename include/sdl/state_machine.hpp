#ifndef STATE_MACHINE_Y2BY8UD4
#define STATE_MACHINE_Y2BY8UD4

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <SDL.h>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace game {
namespace sdl {

template<typename M>
class state_machine : public msm::back::state_machine<M>
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(is_event)

    template<typename T>
    struct event
    {
        typedef typename T::Evt type;
    };

    template<typename T>
    struct events
        : mpl::fold<
              T
            , mpl::vector0<>
            , mpl::if_<
                  has_is_event<event<mpl::_2>>
                , mpl::push_back<mpl::_1, event<mpl::_2>>
                , mpl::_1
              >
          >
    { };

public:
    //using msm::back::state_machine<M>::msm::back::state_machine<M>;
    template<typename... Args>
    state_machine(Args&&... args)
        : msm::back::state_machine<M>(std::forward<Args>(args)...)
    { }

    template<typename TEvent>
    void process_event(const TEvent& event) {
        SDL_Event sdl_event;
        sdl_event.type = SDL_USEREVENT;
        sdl_event.user.code = TEvent::id;
        sdl_event.user.data1 = (void*)&event;
        sdl_event.user.data2 = nullptr;
        SDL_PushEvent(&sdl_event);
    }

    void process_event(const SDL_Event& event) {
        typedef typename msm::back::state_machine<M>::transition_table transition_table;
        for_events<typename events<transition_table>::type>(event);
    }

private:
    template<typename Seq>
    void for_events(const SDL_Event&, typename boost::enable_if<mpl::empty<Seq>>::type* = 0) { }

    template<typename Seq>
    void for_events(const SDL_Event& event, typename boost::disable_if<mpl::empty<Seq>>::type* = 0) {
        typedef typename mpl::front<Seq>::type Event;
        if (event.user.code == Event::id) {
            msm::back::state_machine<M>::process_event(*static_cast<Event*>(event.user.data1));
        } else {
            for_events<typename mpl::pop_front<Seq>::type>(event);
        }
    }
};

} // namespace sdl
} // namespace game

#endif

