#include "Person.h"

Person::Person(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : MovingActor(imageID, startX, startY, startDirection, depth, alive, world), m_infectionStatus(false), m_infectionCount(0)
{
    
}

void Person::doSomething()
{
    
}

Person::~Person()
{
    
}
