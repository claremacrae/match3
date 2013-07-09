#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include "gui/window.hpp"

namespace game {
namespace gui {

window::window(int width, int height, const std::string& caption) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw std::runtime_error("failed SDL_Init: " + std::string(SDL_GetError()));
    }

    window_ = boost::shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            caption.c_str()
          , SDL_WINDOWPOS_CENTERED
          , SDL_WINDOWPOS_CENTERED
          , width
          , height
          , SDL_WINDOW_SHOWN
        )
      , SDL_DestroyWindow
    );

    if (!window_.get()) {
        throw std::runtime_error("failed SDL_CreateWindow: " + std::string(SDL_GetError()));
    }

    renderer_ = boost::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), RENDER_DRIVER, RENDER_FLAGS)
      , SDL_DestroyRenderer
    );

    if (!renderer_.get()) {
        throw std::runtime_error("failed SDL_CreateRenderer: " + std::string(SDL_GetError()));
    }
}

window::~window() {
    quit();
}

void window::quit() {
    SDL_Quit();
}

boost::shared_ptr<SDL_Texture> window::load_image(const std::string& file) const {
    return boost::shared_ptr<SDL_Texture>(
        IMG_LoadTexture(renderer_.get(), file.c_str())
      , SDL_DestroyTexture
    );
}

void window::apply(boost::shared_ptr<SDL_Texture> texture, int x, int y) {
    SDL_Rect pos = { x, y, 0, 0 };
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &pos.w, &pos.h);
    SDL_RenderCopy(renderer_.get(), texture.get(), nullptr, &pos);
}

void window::render() {
    SDL_RenderPresent(renderer_.get());
}

} // namespace gui
} // namespace game

