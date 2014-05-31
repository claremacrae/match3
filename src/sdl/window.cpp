#include <cassert>
#include <stdexcept>
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "sdl/window.hpp"

namespace match3 {
namespace sdl {

window::window(boost::di::named<int, _S("win width")> width
             , boost::di::named<int, _S("win height")> height
             , boost::di::named<std::string, _S("win caption")> caption)
{
    assert(!SDL_Init(SDL_INIT_EVERYTHING) && SDL_GetError());
    assert(!TTF_Init() && TTF_GetError());

    std::string caption_ = caption;
    window_ = std::shared_ptr<SDL_Window>(
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

    renderer_ = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), RENDER_DRIVER, RENDER_FLAGS)
      , SDL_DestroyRenderer
    );

    SDL_SetRenderDrawBlendMode(renderer_.get(), SDL_BLENDMODE_BLEND);
}

window::~window() {
    quit();
}

void window::quit() {
    TTF_Quit();
    SDL_Quit();
}

std::shared_ptr<SDL_Texture> window::load_image(const std::string& file) const {
    return std::shared_ptr<SDL_Texture>(
        IMG_LoadTexture(renderer_.get(), file.c_str())
      , SDL_DestroyTexture
    );
}

std::shared_ptr<SDL_Texture> window::render_text(const std::string& str, const std::string& font_file, SDL_Color color, int font_size) const {
    std::shared_ptr<TTF_Font> font(TTF_OpenFont(font_file.c_str(), font_size), TTF_CloseFont);
    std::shared_ptr<SDL_Surface> surface(TTF_RenderText_Blended(font.get(), str.c_str(), color), SDL_FreeSurface);
    return std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer_.get(), surface.get()), SDL_DestroyTexture);
}

void window::draw(std::shared_ptr<SDL_Texture> texture, int x, int y, std::size_t layer) {
    SDL_Rect pos = {x, y, 0, 0};
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &pos.w, &pos.h);
    layers_[layer].push_back(std::make_pair(texture, pos));
}

void window::fade(Uint8 alpha) {
    SDL_Rect view = {0, 0, 0, 0};
    SDL_RenderGetViewport(renderer_.get(), &view);
    SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, alpha);
    SDL_RenderFillRect(renderer_.get(), &view);
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
    SDL_RenderPresent(renderer_.get());
}

void window::render_layers() {
    for (const auto& layer : layers_) {
        for (const auto& data : layer.second) {
            SDL_RenderCopy(renderer_.get(), data.first.get(), nullptr, &data.second);
        }
    }
    render();
}

} // namespace sdl
} // namespace match3

