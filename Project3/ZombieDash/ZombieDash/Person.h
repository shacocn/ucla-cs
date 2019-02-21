// Represents Penelope and citizens

#ifndef Person_h
#define Person_h

#include "MovingActor.h"

class Person : public MovingActor
{
public:
    Person(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    virtual ~Person();
private:
    bool m_infectionStatus;
    int m_infectionCount;
};

#endif /* Person_h */
