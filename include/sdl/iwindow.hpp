#ifndef IWINDOW_407FC3ZE
#define IWINDOW_407FC3ZE

#include <boost/shared_ptr.hpp>
#include <SDL.h>

namespace game {
namespace sdl {

class iwindow
{
public:
    virtual ~iwindow() { };
    virtual boost::shared_ptr<SDL_Texture> load_image(const std::string&) const = 0;
    virtual boost::shared_ptr<SDL_Texture> render_text(const std::string&, const std::string& = "font.ttf", SDL_Color = {255, 255, 255, 0}, int = 0) const = 0;
    virtual void draw(boost::shared_ptr<SDL_Texture>, int x = 0, int y = 0) = 0;
    virtual void clear() = 0;
    virtual void render() = 0;
    virtual void quit() = 0;
};

} // namespace sdl
} // namespace game

#endif

