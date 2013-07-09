#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <boost/shared_ptr.hpp>
#include "board.hpp"
#include "iviewer.hpp"

namespace game {

class action
{
public:
    BOOST_DI_CTOR(controller
        , const boost::shared_ptr<board>&
        , const boost::shared_ptr<iviewer>&
    );

private:
    boost::shared_ptr<board> board_;
    boost::shared_ptr<iviewer> viewer_;
};

class select_item : public action
{
public:
    using action::action;

    void operator()(const item_selected&);
};

} // namespace game

#endif

