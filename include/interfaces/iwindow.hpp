#ifndef IWINDOW_407FC3ZE
#define IWINDOW_407FC3ZE

#include <memory>
#include <SDL.h>

namespace game {
namespace sdl {

class iwindow
{
public:
    virtual ~iwindow() { };
    virtual std::shared_ptr<SDL_Texture> load_image(const std::string&) const = 0;
    virtual std::shared_ptr<SDL_Texture> render_text(const std::string&, const std::string&, SDL_Color, int) const = 0;
    virtual void draw(std::shared_ptr<SDL_Texture>, int x = 0, int y = 0, std::size_t = 0) = 0;
    virtual void fade(Uint8) = 0;
    virtual void clear() = 0;
    virtual void clear(std::size_t) = 0;
    virtual void render() = 0;
    virtual void render_layers() = 0;
    virtual void quit() = 0;
};

} // namespace sdl
} // namespace game

#endif

