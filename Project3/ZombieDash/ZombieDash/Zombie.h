#ifndef Zombie_h
#define Zombie_h
#include "MovingActor.h"

class Zombie : public MovingActor
{
public:
    Zombie(int imageID, int startX, int startY, Direction startDirection, int depth);
    virtual void doSomething();
    virtual ~Zombie();
private:
};

#endif /* Zombie_h */
