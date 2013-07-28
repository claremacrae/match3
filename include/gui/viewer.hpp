#ifndef VIEWER_ZTZFA603
#define VIEWER_ZTZFA603

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/di/ctor.hpp>
#include <boost/di/named.hpp>
#include <mpl/string.hpp>
#include "iwindow.hpp"
#include "iviewer.hpp"
#include "position.hpp"

namespace game {
namespace gui {

class viewer : public iviewer
{
    const std::string images_dir        = "images/";
    const std::string background_image  = "background.png";
    const std::string select_image      = "select.png";
    const std::string match_image       = "match.png";
    const std::string font              = "font.ttf";

    const SDL_Color black               = {0, 0, 0, 0};
    const SDL_Color white               = {255, 255, 255, 0};

    const int grid_size                 = 38;
    const int grid_offset               = grid_size + 5;
    const int grids_offset_x            = 328;
    const int grids_offset_y            = 100;

    enum {
        background_layer
      , board_layer
      , board_actions_layer
      , text_time_layer
      , text_points_layer
    };

public:
    BOOST_DI_CTOR(viewer
        , boost::shared_ptr<sdl::iwindow>
        , boost::di::named<int, _S("board colors")>);

    virtual void quit() override;
    virtual void render() override;
    virtual void clear_board() override;
    virtual void show_grid(const position&, color_t) override;
    virtual void show_match(const position&) override;
    virtual void select_item(const position&) override;
    virtual void show_time(int) override;
    virtual void show_points(int) override;
    virtual void show_results(int) override;
    virtual void fade_screen(sdl::milliseconds_t) override;

private:
    void show_text(const std::string&, int, int, SDL_Color, int, std::size_t);

    boost::shared_ptr<sdl::iwindow> window_;
    boost::shared_ptr<SDL_Texture> background_image_;
    boost::shared_ptr<SDL_Texture> match_image_;
    boost::shared_ptr<SDL_Texture> select_image_;
    std::map<color_t, boost::shared_ptr<SDL_Texture>> grid_images_;
};

} // namespace gui
} // namespace game

#endif

