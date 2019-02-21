#ifndef Goodie_h
#define Goodie_h
#include "StaticActor.h"

class Goodie : public StaticActor
{
public:
    Goodie(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    ~Goodie();
};

#endif /* Goodie_h */
