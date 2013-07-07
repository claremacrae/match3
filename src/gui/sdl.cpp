#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL_image.h>
#include "gui/sdl.hpp"

namespace game {
namespace gui {

sdl::sdl(int width, int height, int bpp, const std::string& caption) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw std::runtime_error("failed SDL_Init: " + std::string(SDL_GetError()));
    }

    screen_ = SDL_SetVideoMode(width, height, bpp, SDL_DOUBLEBUF | SDL_HWSURFACE);

    if (screen_ == nullptr) {
        throw std::runtime_error("failed SDL_SetVideoMode: " + std::string(SDL_GetError()));
    }

    SDL_WM_SetCaption(caption.c_str(), nullptr);
}

sdl::~sdl() {
    SDL_FreeSurface(screen_);
    SDL_Quit();
}

boost::shared_ptr<SDL_Surface> sdl::load_image(const std::string& file) const {
    return boost::shared_ptr<SDL_Surface>(IMG_Load(file.c_str()), SDL_FreeSurface);
}

void sdl::apply_surface(boost::shared_ptr<SDL_Surface> surface, int x, int y) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(surface.get(), nullptr, screen_, &offset);
}

void sdl::refresh() {
    if (SDL_Flip(screen_) == -1) {
        throw std::runtime_error("failed SDL_Flip: " + std::string(SDL_GetError()));
    }
}

} // namespace gui
} // namespace game

