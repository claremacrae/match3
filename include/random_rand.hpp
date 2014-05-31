#ifndef RANDOM_RAND_UGD9LGT8
#define RANDOM_RAND_UGD9LGT8

#include <random>
#include "irandom.hpp"

namespace match3 {

class random_rand : public irandom
{
public:
    int get_random_number(int, int) const override;
};

} // namespace match3

#endif

