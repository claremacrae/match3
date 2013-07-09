#ifndef IVIEWER_T977IO6T
#define IVIEWER_T977IO6T

#include "detail/position.hpp"
#include "detail/common.hpp"

namespace game {

class iviewer
{
public:
    virtual ~iviewer() { }
    virtual void set_background() = 0;
    virtual void quit() = 0;
    virtual void render() = 0;
    virtual void show_grid(const detail::position&, detail::color_t) = 0;
    virtual void show_match(const detail::position&) = 0;
    virtual void select_item(const detail::position&) = 0;
};

} // namespace game

#endif

