#include "SmartZombie.h"

SmartZombie::SmartZombie(double startX, double startY, StudentWorld* world) : Zombie(IID_ZOMBIE, startX, startY, 0, 0, true, world)
{
    /*
     
     same image id
     if created from infected person than it must have that starting lcoation, other wise studentworld passes it in as usual
     same direction
     same depth of 0
     
     movement plan distance of 0
     alive state
     
     */
}

void SmartZombie::doSomething()
{
    /*
     
     idea: there's prolly gonna be a parameter that takes in the ratio 1/3 VS 1/10 for the dumb zombie
     
     - check if it's alive; return if not
     - becomes paralyzed every even tick
     - check to see if a person is in front of it in the direction it is facing
            - compute vomit coordinates
            - if there is a person whose euclidean distance <= 10px then 1/3 chance that it will vomit
                    - introduce vomit object, play SOUND_ZOMBIE_VOMIT
                    - return and do nothing
     - check to see if it needs a new movement plan bc movement plan reached 0
            - pick new random movement plan in the range 3 to 10
            - select person closest to the smart zombie (smallest euclidean distance) select one if two exist
            - set direction to a random direction
                    - if the distance to the selected nearest person is more than 80px away, then random is chosen from up, down, left, and right
                    - otherwise, choose direction that gets zombie closest to that person
                            - if zombie is on the same row col choose the ONLY direction that gets the zombie closer, otherwise choose randomly between two directions vertical or horizontal that gets zombie closer
     - smart zombie determines destination coordinate 1 px in front of it
     - if no intersection of wall person or other zombie, update location using moveTo as usual and decrease movemnent plan by 1
     - otherwise, set movement plan to 0
     
     
     details:
     - can be damaged by flames
     - if flame overlaps with zombie, kills smart zombie by : setting own state to dead, play sound effect SOUND_ZOMBIE_DIE and increase player's score by 2000 points
     - cannot be infected by vomit
     - smart zombie blocks other objects from moving nearby onto it
     - cannot block flames
     
     
     */
}

SmartZombie::~SmartZombie()
{
    
}
