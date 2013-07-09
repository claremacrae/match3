#ifndef SDL_80DDRNSJ
#define SDL_80DDRNSJ

#include "gui/isdl.hpp"
#include <boost/shared_ptr.hpp>

namespace game {
namespace gui {

class sdl : public isdl
{
public:
    explicit sdl(int width = 755, int height = 600, int bpp = 32, const std::string& caption = "");
    virtual ~sdl();

    virtual boost::shared_ptr<SDL_Surface> load_image(const std::string&) const override;
    virtual void apply_surface(boost::shared_ptr<SDL_Surface> surface, int x, int y) override;
    virtual void refresh() override;
    virtual void stop() override;

private:
    SDL_Surface* screen_ = nullptr; // cant be used within boost::shared_ptr
};

} // namespace gui
} // namespace game

#endif

