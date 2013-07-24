#ifndef MSM_KRNOGIYP
#define MSM_KRNOGIYP

#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <SDL.h>

namespace mpl  = boost::mpl;
namespace back = boost::msm::back;

namespace game {
namespace sdl {

template<typename M>
class msm : public back::state_machine<M>
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(id)

    template<typename T>
    struct event
    {
        typedef typename T::Evt type;
    };

    template<typename T>
    using events = typename mpl::transform<T, event<mpl::_1>>::type;

public:
    template<typename... Args>
    explicit msm(Args&&... args)
        : back::state_machine<M>(std::forward<Args>(args)...)
    { }

    template<typename TEvent>
    void process_event(const TEvent& event) {
        SDL_Event sdl_event = build_sdl_event(event);
        SDL_PushEvent(&sdl_event);
    }

    void process_event(const SDL_Event& event) {
        typedef typename back::state_machine<M>::transition_table transition_table;
        for_events<typename events<transition_table>::type>(event);
    }

private:
    template<typename Seq>
    void for_events(const SDL_Event&, typename std::enable_if<mpl::empty<Seq>::value>::type* = 0) { }

    template<typename Seq>
    void for_events(const SDL_Event& event, typename std::enable_if<!mpl::empty<Seq>::value>::type* = 0) {
        typedef typename mpl::front<Seq>::type event_t;
        if (event.type == SDL_USEREVENT and is_same_id<event_t>(event.user.code)) {
            back::state_machine<M>::process_event(*static_cast<event_t*>(event.user.data1));
        } else if (is_same_id<event_t>(event.type)) {
            process_event_impl<event_t>(event);
        } else {
            for_events<typename mpl::pop_front<Seq>::type>(event);
        }
    }

    template<typename TEvent>
    typename std::enable_if<!std::is_constructible<TEvent, const SDL_Event&>::value>::type
    process_event_impl(const SDL_Event&) {
        back::state_machine<M>::process_event(TEvent());
    }

    template<typename TEvent>
    typename std::enable_if<std::is_constructible<TEvent, const SDL_Event&>::value>::type
    process_event_impl(const SDL_Event& event) {
        back::state_machine<M>::process_event(TEvent(event));
    }

    template<typename TEvent>
    SDL_Event&& build_sdl_event(const TEvent& event) {
        SDL_Event sdl_event;
        sdl_event.type = SDL_USEREVENT;
        sdl_event.user.code = TEvent::id::value;
        sdl_event.user.data1 = (void*)&event;
        sdl_event.user.data2 = nullptr;
        return std::move(sdl_event);
    }

    template<typename TEvent>
    static bool is_same_id(int value, typename std::enable_if<has_id<TEvent>::value>::type* = 0) {
        return value == TEvent::id::value;
    }

    template<typename TEvent>
    static bool is_same_id(int, typename std::enable_if<!has_id<TEvent>::value>::type* = 0) {
        return false;
    }
};

} // namespace sdl
} // namespace game

#endif

