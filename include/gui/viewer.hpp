#ifndef VIEWER_ZTZFA603
#define VIEWER_ZTZFA603

#include <map>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "gui/iwindow.hpp"
#include "iviewer.hpp"
#include "detail/position.hpp"
#include "detail/common.hpp"

namespace game {
namespace gui {

class win_width { };
class win_height { };

class viewer : public iviewer
{
    const std::string images_dir          = "images/";
    const std::string background_image    = "background.png";
    const std::string select_image        = "select.png";
    const std::string match_image         = "match.png";

public:
    BOOST_DI_CTOR(viewer
        , boost::shared_ptr<iwindow>
    );

    virtual void set_background() override;
    virtual void quit() override;
    virtual void render() override;
    virtual void show_grid(const detail::position&, detail::color_t) override;
    virtual void show_match(const detail::position&) override;
    virtual void select_item(const detail::position&) override;

private:
    boost::shared_ptr<gui::iwindow> window_;
    boost::shared_ptr<SDL_Texture> background_image_;
    boost::shared_ptr<SDL_Texture> match_image_;
    boost::shared_ptr<SDL_Texture> select_image_;
    std::map<detail::color_t, boost::shared_ptr<SDL_Texture>> grid_images_;
};

} // namespace tui
} // namespace game

#endif

