#ifndef SmartZombie_h
#define SmartZombie_h
#include "Zombie.h"

class SmartZombie : public Zombie
{
public:
    SmartZombie(double startX, double startY);
    virtual void doSomething();
    virtual ~SmartZombie();
};

#endif /* SmartZombie_h */
