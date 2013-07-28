#ifndef IPOINTS_SF7WXM00
#define IPOINTS_SF7WXM00

namespace game {

class ipoints
{
public:
    virtual ~ipoints() { };
    virtual void add(int) = 0;
    virtual void sub(int) = 0;
    virtual operator int() const = 0;
};

} // namespace game

#endif

