#ifndef WINDOW_80DDRNSJ
#define WINDOW_80DDRNSJ

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/di.hpp>
#include <mpl/string.hpp>
#include "sdl/iwindow.hpp"

namespace game {
namespace sdl {

class window : public iwindow
{
    const int RENDER_DRIVER = -1;
    const int RENDER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    typedef std::pair<boost::shared_ptr<SDL_Texture>, SDL_Rect> texture_rect_t;
    typedef std::map<int, std::vector<texture_rect_t>> layers_t;

public:
    BOOST_DI_CTOR(window
        , boost::di::named<int, _S("win width")>
        , boost::di::named<int, _S("win height")>
        , boost::di::named<std::string, _S("win caption")>);

    virtual ~window();
    virtual boost::shared_ptr<SDL_Texture> load_image(const std::string&) const override;
    virtual boost::shared_ptr<SDL_Texture> render_text(const std::string&, const std::string&, SDL_Color, int) const override;
    virtual void draw(boost::shared_ptr<SDL_Texture>, int, int, std::size_t) override;
    virtual void clear() override;
    void clear(std::size_t) override;
    virtual void render() override;
    virtual void quit() override;

private:
    boost::shared_ptr<SDL_Window> window_;
    boost::shared_ptr<SDL_Renderer> renderer_;
    layers_t layers_;
};

} // namespace sdl
} // namespace game

#endif

