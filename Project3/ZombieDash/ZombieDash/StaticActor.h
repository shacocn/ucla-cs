#ifndef StaticActor_h
#define StaticActor_h
#include "Actor.h"

class StaticActor : public Actor
{
public:
    StaticActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    virtual ~StaticActor();
};

#endif /* StaticActor_h */
