#ifndef Weapon_hpp
#define Weapon_hpp
#include "StaticActor.h"

class Weapon : public StaticActor
{
public:
    Weapon(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    ~Weapon();
private:
};

#endif /* Weapon_hpp */
