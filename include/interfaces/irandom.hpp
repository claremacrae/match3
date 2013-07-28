#ifndef IRANDOM_S84J5C6T
#define IRANDOM_S84J5C6T

namespace game {

class irandom
{
public:
    virtual ~irandom() { }
    virtual int get_random_number(int, int) const = 0;
};

} // namespace game

#endif

