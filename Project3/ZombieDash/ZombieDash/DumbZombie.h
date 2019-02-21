#ifndef DumbZombie_h
#define DumbZombie_h

#include "Zombie.h"

class DumbZombie : public Zombie
{
public:
    DumbZombie(double startX, double startY);
    virtual void doSomething();
    virtual ~DumbZombie();
};

#endif /* DumbZombie_h */
