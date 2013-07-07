#ifndef VIEWER_ZTZFA603
#define VIEWER_ZTZFA603

#include <map>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include "gui/isdl.hpp"
#include "iviewer.hpp"
#include "detail/position.hpp"
#include "detail/common.hpp"

namespace game {
namespace gui {

class win_width { };
class win_height { };
class images_dir { };

class viewer : public iviewer
{
    const std::string background_image    = "background.png";
    const std::string select_image        = "select.png";
    const std::string match_image         = "match.png";

public:
    BOOST_DI_CTOR(viewer
        , boost::di::named<std::string, images_dir>
        , const boost::shared_ptr<isdl>&
    );

    virtual void init() override;
    virtual void refresh() override;
    virtual void show_grid(const detail::position&, detail::color_t) override;
    virtual void show_match(const detail::position&) override;
    virtual void select_item(const detail::position&) override;

private:
    std::string images_dir_;
    boost::shared_ptr<gui::isdl> sdl_;
    boost::shared_ptr<SDL_Surface> background_image_;
    boost::shared_ptr<SDL_Surface> match_image_;
    std::map<detail::color_t, boost::shared_ptr<SDL_Surface>> grid_images_;
};

} // namespace tui
} // namespace game

#endif

