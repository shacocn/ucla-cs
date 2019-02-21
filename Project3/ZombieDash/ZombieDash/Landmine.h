#ifndef Landmine_h
#define Landmine_h

#include "Weapon.h"

class Landmine : public Weapon
{
public:
    Landmine(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    ~Landmine();
};

#endif /* Landmine_h */
