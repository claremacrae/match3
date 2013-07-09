#ifndef I_407FC3ZE
#define I_407FC3ZE

#include <boost/shared_ptr.hpp>
#include <SDL.h>
#include <SDL_image.h>

namespace game {
namespace gui {

class iwindow
{
public:
    virtual ~iwindow() { };

    virtual boost::shared_ptr<SDL_Texture> load_image(const std::string&) const = 0;
    virtual void apply(boost::shared_ptr<SDL_Texture> surface, int x = 0, int y = 0) = 0;
    virtual void render() = 0;
    virtual void quit() = 0;
};

} // namespace gui
} // namespace game

#endif

