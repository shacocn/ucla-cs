#include "LandmineGoodie.h"

LandmineGoodie::LandmineGoodie(double startX, double startY) : Goodie(IID_LANDMINE_GOODIE, startX, startY, 0, 1)
{
    /*
     
     - image id as usual
     - starting loc as usual
     - direction as usual
     - landmine goodie has depth of 1
     - alive status
     
     */
}

void LandmineGoodie::doSomething()
{
    /*
     
     check to see if it is alive; if not return
     determine if overlaps with PENNY only
     if yes:
        inform studentworld object that the user is to receive 50 points
        set state to dead
        play sound effect GOT GOODIE
        inform SW object that penelope gets to receive 2 landmines
     
     details:
     can be damaged by flames; set status to dead
     cannot be infected by vomit
     does not block other objects from moving nearby/onto them
     
     */
}


LandmineGoodie::~LandmineGoodie()
{
    
}
