#include "Exit.h"

Exit::Exit(double startX, double startY) : StaticActor(IID_EXIT, startX, startY, 0, 1)
{
    /*
     
     - pass in image id
     - same starting position (hint, studentworld object can pass this in when constructing object
     - same direction as penelope
     - depth is 1, NOT 0
     
     */
}

void Exit::doSomething()
{
    /*
     
     - must determine if overlaps with citizen BUT NOT PENELOPE
        - if there is overlap
            - inform the studentworld that the user receives 500 points
            - set citizen object's state to dead BUT must not kill the citizen in a way that deducts points from the player as if the citizen died due to a zombie infection, a flame, or a pit
            - play sound affect SOUND_CITIZEN_SAVED
     - determine if it overlaps with penelope
        - if so AND all citizens have either exited level or died (if none exist on the level), then inform student world object that penelope has finished current level
     
     
     OTHER DETAILS:
     - cannot be damaged by flame
     - cannot be infected by vomit
     - cannot block other objects from moving nearby/onto them
     - DOES block flame 
     */
}

Exit::~Exit()
{
    
}
