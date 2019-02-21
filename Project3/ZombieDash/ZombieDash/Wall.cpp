#include "Wall.h"

Wall::Wall(double startX, double startY, StudentWorld* world) : StaticActor(IID_WALL, startX, startY, 0, 0, true, world)
{
}

void Wall::doSomething()
{
    // do nothing.
    
    /*
     
     other details:
     - cannot be damaged by flame
     - cannot be infected by vomit
     - blocks movement of citizens, zombies, and penelope
            - bounding box cannot intersect actor's bounding box
     - wall blocks flames (cannot be created past a wall)
     
     */
}


Wall::~Wall()
{
    
}
