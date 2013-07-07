#ifndef RANDOM_MOCK_B1407EUU
#define RANDOM_MOCK_B1407EUU

#include <gmock/gmock.h>
#include "irandom.hpp"

namespace game {
namespace test {
namespace mocks {

class random_mock : public irandom
{
public:
    MOCK_CONST_METHOD2(get_random_number, int(int, int));
};

} // namespace mocks
} // namespace test
} // namespace game

#endif

