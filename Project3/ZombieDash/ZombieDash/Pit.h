#ifndef Pit_h
#define Pit_h

#include "Weapon.h"

class Pit : public Weapon
{
public:
    Pit(double startX, double startY);
    virtual void doSomething();
    virtual ~Pit();
private:
};

#endif /* Pit_h */
