#ifndef WINDOW_80DDRNSJ
#define WINDOW_80DDRNSJ

#include <map>
#include <vector>
#include <memory>
#include <boost/di.hpp>
#include <mpl/string.hpp>
#include "iwindow.hpp"

namespace match3 {
namespace sdl {

class window : public iwindow
{
    const int RENDER_DRIVER = -1;
    const int RENDER_FLAGS  = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    typedef std::pair<std::shared_ptr<SDL_Texture>, SDL_Rect> texture_rect_t;
    typedef std::map<int, std::vector<texture_rect_t>> layers_t;

public:
    window(boost::di::named<int, _S("win width")>
         , boost::di::named<int, _S("win height")>
         , boost::di::named<std::string, _S("win caption")>);

    ~window() override;
    std::shared_ptr<SDL_Texture> load_image(const std::string&) const override;
    std::shared_ptr<SDL_Texture> render_text(const std::string&, const std::string&, SDL_Color, int) const override;
    void draw(std::shared_ptr<SDL_Texture>, int, int, std::size_t) override;
    void fade(Uint8) override;
    void clear() override;
    void clear(std::size_t) override;
    void render() override;
    void render_layers() override;
    void quit() override;

private:
    std::shared_ptr<SDL_Window> window_;
    std::shared_ptr<SDL_Renderer> renderer_;
    layers_t layers_;
};

} // namespace sdl
} // namespace match3

#endif

