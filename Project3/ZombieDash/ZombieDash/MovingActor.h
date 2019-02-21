#ifndef MovingActor_h
#define MovingActor_h

#include "Actor.h"

class MovingActor : public Actor
{
public:
    MovingActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    virtual ~MovingActor();
private:
};

#endif /* MovingActor_h */
