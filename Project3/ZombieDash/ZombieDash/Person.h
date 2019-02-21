// Represents Penelope and citizens

#ifndef Person_h
#define Person_h

#include "MovingActor.h"

class Person : public MovingActor
{
public:
    Person(int imageID, int startX, int startY, Direction startDirection, int depth);
    virtual void doSomething();
    virtual ~Person();
};

#endif /* Person_h */
