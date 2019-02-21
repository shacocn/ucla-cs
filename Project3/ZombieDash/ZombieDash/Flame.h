#ifndef Flame_h
#define Flame_h

#include "Projectile.h"

class Flame : public Projectile
{
public:
    Flame(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Flame();
private:
};

#endif /* Flame_h */
