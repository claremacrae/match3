#ifndef VIEWER_ZTZFA603
#define VIEWER_ZTZFA603

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <mpl_string.hpp>
#include "detail/position.hpp"
#include "sdl/iwindow.hpp"
#include "iviewer.hpp"

namespace game {
namespace gui {

class viewer : public iviewer
{
    const std::string images_dir          = "images/";
    const std::string background_image    = "background.png";
    const std::string select_image        = "select.png";
    const std::string match_image         = "match.png";

public:
    BOOST_DI_CTOR(viewer
        , boost::shared_ptr<sdl::iwindow>
        , boost::di::named<int, _S("grid offset")>
        , boost::di::named<int, _S("grids offset x")>
        , boost::di::named<int, _S("grids offset y")>
        , boost::di::named<int, _S("board colors")>
        , boost::di::named<std::string, _S("font name")>
        , boost::di::named<int, _S("font size")>
    );

    virtual void set_background() override;
    virtual void quit() override;
    virtual void render() override;
    virtual void show_grid(const detail::position&, detail::color_t) override;
    virtual void show_match(const detail::position&) override;
    virtual void select_item(const detail::position&) override;
    virtual void show_text(const std::string& str, int x, int y) override;

private:
    boost::shared_ptr<sdl::iwindow> window_;
    boost::shared_ptr<SDL_Texture> background_image_;
    boost::shared_ptr<SDL_Texture> match_image_;
    boost::shared_ptr<SDL_Texture> select_image_;
    std::map<detail::color_t, boost::shared_ptr<SDL_Texture>> grid_images_;
    int grid_offset_ = 0;
    int grids_offset_x_ = 0;
    int grids_offset_y_ = 0;
    int colors_ = 0;
    std::string font_ = "";
    int font_size_ = 0;
};

} // namespace gui
} // namespace game

#endif

