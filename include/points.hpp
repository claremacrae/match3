#ifndef POINTS_TQVMGAEK
#define POINTS_TQVMGAEK

#include "interfaces/ipoints.hpp"

namespace match3 {

class points : public ipoints
{
public:
    void add(int) override;
    void sub(int) override;
    operator int() const override;

private:
    int points_ = 0;
};

} // namespace match3

#endif

