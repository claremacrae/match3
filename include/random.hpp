#include <random>
#include "irandom.hpp"

namespace game {

class random : public irandom
{
public:
    virtual int get_random_number(int, int) const override;
};

} // namespace game

