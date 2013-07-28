#ifndef POINTS_TQVMGAEK
#define POINTS_TQVMGAEK

#include "interfaces/ipoints.hpp"

namespace game {

class points : public ipoints
{
public:
    virtual void add(int) override;
    virtual void sub(int) override;
    virtual operator int() const override;

private:
    int points_ = 0;
};

} // namespace game

#endif

