#ifndef RANDOM_MT19937_3W2CDX8T
#define RANDOM_MT19937_3W2CDX8T

#include <random>
#include "irandom.hpp"

namespace game {

class random_mt19937 : public irandom
{
public:
    virtual int get_random_number(int, int) const override;
};

} // namespace game

#endif

