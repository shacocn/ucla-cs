#include "Flame.h"

Flame::Flame(double startX, double startY, StudentWorld* world) : Projectile(IID_FLAME, startX, startY, 0, 0, true, world)
{
    /*
     
     - pass in ID as usual
     - starting location flame must be specified during construction
     - starting direction of flame must be specified during construction
     - depth is 0
     - starts in alive state (BOOLEAN)
     
     */
}

void Flame::doSomething()
{
    /*
     
     - check to see if it is currently alive
            - if not, return immediately
     - two ticks from creation, flame must set state to dead so it can be destroyed and removed from the level by the StudentWorld object and return immediately
     - otherwise, damage all damageable objects that overlap with the flame
            - penny, citizens, goodies, landmines, and all zombies included
     
     
     
     OTHER DETAILS:
     - cannot be damaged by another flame
     - cannot be infected by vomit
     - does not blcok other objects
     
     */
}


Flame::~Flame()
{
    
}
