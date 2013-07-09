#ifndef ISDL_407FC3ZE
#define ISDL_407FC3ZE

#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>

namespace game {
namespace gui {

class isdl
{
public:
    virtual ~isdl() { };

    virtual boost::shared_ptr<SDL_Surface> load_image(const std::string&) const = 0;
    virtual void apply_surface(boost::shared_ptr<SDL_Surface> surface, int x = 0, int y = 0) = 0;
    virtual void refresh() = 0;
    virtual void stop() = 0;
};

} // namespace gui
} // namespace game

#endif

