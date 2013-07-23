#include <cassert>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "sdl/window.hpp"

namespace game {
namespace sdl {

window::window(boost::di::named<int, _S("win width")> width
             , boost::di::named<int, _S("win height")> height
             , boost::di::named<std::string, _S("win caption")> caption)
{
    assert(!SDL_Init(SDL_INIT_EVERYTHING) && SDL_GetError());
    assert(!TTF_Init() && TTF_GetError());

    std::string caption_ = caption;
    window_ = boost::shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            caption_.c_str()
          , SDL_WINDOWPOS_CENTERED
          , SDL_WINDOWPOS_CENTERED
          , width
          , height
          , SDL_WINDOW_SHOWN
        )
      , SDL_DestroyWindow
    );

    renderer_ = boost::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), RENDER_DRIVER, RENDER_FLAGS)
      , SDL_DestroyRenderer
    );
}

window::~window() {
    quit();
}

void window::quit() {
    TTF_Quit();
    SDL_Quit();
}

boost::shared_ptr<SDL_Texture> window::load_image(const std::string& file) const {
    return boost::shared_ptr<SDL_Texture>(
        IMG_LoadTexture(renderer_.get(), file.c_str())
      , SDL_DestroyTexture
    );
}

boost::shared_ptr<SDL_Texture> window::render_text(const std::string& str, const std::string& font_file, SDL_Color color, int font_size) const {
    boost::shared_ptr<TTF_Font> font(TTF_OpenFont(font_file.c_str(), font_size), TTF_CloseFont);
    boost::shared_ptr<SDL_Surface> surface(TTF_RenderText_Blended(font.get(), str.c_str(), color), SDL_FreeSurface);
    return boost::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer_.get(), surface.get()), SDL_DestroyTexture);
}

void window::draw(boost::shared_ptr<SDL_Texture> texture, int x, int y, std::size_t layer) {
    SDL_Rect pos = {x, y, 0, 0};
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &pos.w, &pos.h);
    layers_[layer].push_back(std::make_pair(texture, pos));
}

void window::clear() {
    layers_.clear();
    SDL_RenderClear(renderer_.get());
}

void window::clear(std::size_t layer) {
    if (layers_.find(layer) != layers_.end()) {
        layers_[layer].clear();
    }
}

void window::render() {
    for (const auto& layer : layers_) {
        for (const auto& data : layer.second) {
            SDL_RenderCopy(renderer_.get(), data.first.get(), nullptr, &data.second);
        }
    }
    SDL_RenderPresent(renderer_.get());
}

} // namespace sdl
} // namespace game

