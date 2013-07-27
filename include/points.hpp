#ifndef POINTS_TQVMGAEK
#define POINTS_TQVMGAEK

namespace game {

class points
{
public:
    void add(int);
    void sub(int);
    operator int() const;

private:
    int points_ = 0;
};

} // namespace game

#endif

