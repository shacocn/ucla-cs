#include "VaccineGoodie.h"

VaccineGoodie::VaccineGoodie(double startX, double startY) : Goodie(IID_VACCINE_GOODIE, startX, startY, 0, 1)
{
    /*
     
     - image id as usual
     - starting location as usual
     - regular direction
     - DEPTH of 1
     - starts in alive state
     
     */
}


void VaccineGoodie::doSomething()
{
    /*
     
     - check to see if alive; if not, return
     - must determine if overlaps with penelope
     - if yes
            - inform studentworld object that user is to receive 50 points
            - set state to dead
            - play sound effect to indicate penelope picked up goodie
            - inform studentworld object that penelope is to receive one dose of vaccine
     
     details
     - can be damaged by flame
            - sets status to dead when hit
     - cannot be infected by vomit
     - does not block object from moving onto it
     
     */
}


VaccineGoodie::~VaccineGoodie()
{
    
}
