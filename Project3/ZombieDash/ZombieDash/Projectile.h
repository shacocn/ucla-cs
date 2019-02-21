#ifndef Projectile_h
#define Projectile_h
#include "Weapon.h"

class Projectile : public Weapon
{
public:
    Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    ~Projectile();
};

#endif /* Projectile_h */
