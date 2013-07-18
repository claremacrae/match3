#ifndef WINDOW_80DDRNSJ
#define WINDOW_80DDRNSJ

#include "sdl/iwindow.hpp"
#include <boost/shared_ptr.hpp>

namespace game {
namespace sdl {

class window : public iwindow
{
    const int RENDER_DRIVER = -1;
    const int RENDER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

public:
    explicit window(int width = 755, int height = 600, const std::string& caption = "");
    virtual ~window();

    virtual boost::shared_ptr<SDL_Texture> load_image(const std::string&) const override;
    virtual boost::shared_ptr<SDL_Texture> render_text(const std::string&, const std::string&, SDL_Color, int) const override;
    virtual void draw(boost::shared_ptr<SDL_Texture>, int, int) override;
    virtual void clear() override;
    virtual void render() override;
    virtual void quit() override;

private:
    boost::shared_ptr<SDL_Window> window_;
    boost::shared_ptr<SDL_Renderer> renderer_;
};

} // namespace sdl
} // namespace game

#endif

