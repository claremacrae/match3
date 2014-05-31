#ifndef ROW_BHDK37RD
#define ROW_BHDK37RD

#include <vector>
#include "grid.hpp"

namespace match3 {

class row
{
    typedef std::vector<grid> grids_t;

public:
    explicit row(int cols)
        : grids_(cols)
    { }

    grids_t::reference operator[](std::size_t i) {
        return grids_[i];
    }

private:
    grids_t grids_;
};

} // namespace match3

#endif

