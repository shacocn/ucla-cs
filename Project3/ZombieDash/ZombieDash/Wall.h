#ifndef Wall_h
#define Wall_h

#include "StaticActor.h"

class Wall : public StaticActor
{
public:
    Wall(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Wall();
private:
    
};

#endif /* Wall_h */
