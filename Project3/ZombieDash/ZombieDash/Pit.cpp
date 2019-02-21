#include "Pit.h"

Pit::Pit(double startX, double startY, StudentWorld* world) : Weapon(IID_PIT, startX, startY, 0, 0, true, world)
{
   /*
    
    - same image ID
    - same location start
    - same direction
    - same depth 0
    
    */
}

void Pit::doSomething()
{
    /*
     
     - any person or zombie that overlaps it must be destroyed
     - being destroyed is the same as being damaged by flame (dumb zombie falling into pit is 1000 points, game plays dying noise; if penny falls into pit, current level ends and player loses 1000 points)
     
     
     OTHER CIRCUMSTANCES:
     - a pit cannot be damaged by flame
     - pit cannot be infected by vomit
     - pit does not block movement of actors
     - pit does not block vomit or flames
     
     */
}

Pit::~Pit()
{
    
}
