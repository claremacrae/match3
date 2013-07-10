#ifndef RANDOM_RAND_UGD9LGT8
#define RANDOM_RAND_UGD9LGT8

#include <random>
#include "irandom.hpp"

namespace game {

class random_rand : public irandom
{
public:
    virtual int get_random_number(int, int) const override;
};

} // namespace game

#endif

