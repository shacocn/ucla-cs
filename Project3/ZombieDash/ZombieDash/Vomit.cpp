#include "Vomit.h"

Vomit::Vomit(double startX, double startY, StudentWorld* world) : Projectile(IID_VOMIT, startX, startY, 0, 0, true, world)
{
    /*
     
     pass in image ID
     starting location must be specified
     starting direction must be specified
     vomit object has depth of 0
     starts in alive state (boolean alive/dead)
     
     */
}

void Vomit::doSomething()
{
    /*
     
     - check to see if it is alive
            - return immediately if it is dead
     - two ticks from creation, vomit must set state to dead so it can be destroyed and removed from level by StudentWorld object
     - infect all infectable objects that overlap with vomit
            - penelope and citizens
     
     details:
     - cannot be damaged by flame
     - vomit cannot be infected by vomit
     - vomit does not block other objects from moving nearby/onto it
     
     */
}

Vomit::~Vomit()
{
    
}
