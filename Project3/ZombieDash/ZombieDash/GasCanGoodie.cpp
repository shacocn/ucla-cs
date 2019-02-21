#include "GasCanGoodie.h"

GasCanGoodie::GasCanGoodie(double startX, double startY) : Goodie(IID_GAS_CAN_GOODIE, startX, startY, 0, 1)
{
    /*
     
     - image id as usual
     - starting location as usual
     - direction as usual
     - DEPTH OF 1
     - starts in alive state
     
     */
}


void GasCanGoodie::doSomething()
{
    /*
     
     - check to see if it is alive
            - return if dead
     - determines if overlaps with penelope
            - tell studentworld that user is to receive 50 points
            - set state to dead
            - play sound affect SOUND_GOT_GOODIE
            - inform studentworld object that penny gets 5 charges for her flamethrower
     
     
     details:
     - can be damaged by flame
            - set status to dead if so
     - cannot be infected by vomit
     - does not block other objects from moving onto it
     
     */
}

GasCanGoodie::~GasCanGoodie()
{
    
}
