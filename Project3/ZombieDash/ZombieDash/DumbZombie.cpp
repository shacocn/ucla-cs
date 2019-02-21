#include "DumbZombie.h"

DumbZombie::DumbZombie(double startX, double startY) : Zombie(IID_ZOMBIE, startX, startY, 0, 0)
{
    /*
     
     
     x image ID as usual
     - if object was created because infected person became zombie, pass in the starting location
     - otherwise start at the current level's data file
     - studentworld constructs this when it starts
     - same direction
     - same depth
     
     
     - movement plan distance of 0
     - starts alive
     
     */
}

void DumbZombie::doSomething()
{
    /*
     
     potential methods?
     - isEvenTick()
     - getEuclideanDistance() -- put in same class as one that holds distance variables
     
     - check to see if is currently alive; return if not
     - even ticks paralyze zombie (doesn't do anything, just returns)
     - odd ticks: check to see if a person is in front of it (either penelope or one of citizens) in direction its facing
            - checks vomit coordiantes in direction it is facing SPRITE_WIDTH px away if facing left or right or SPRITE_HEIGHT px away if facing up or down
            - would be (x-SPRITE_WIDTH, y) if it was facing left
            - if there is a person whose euclidean distance from the vomit coordinates is less than or equal to 10 px, then there is a 1 in 3 chance that the dumb zombie will vomit
            - if vomit,
                    - introduce a vomit object into the game at the vomit coordinates
                    - play SOUND_ZOMBIE_VOMIT and return
     - check to see if it needs a new movement plan because current movement plan distance has reached 0; if so:
            - pick new random movement plan distance in the range 3 to 10 inclusive
            - set direction to a random direction (up, down, left, or right)
     - determine destination coordinate that is 1 px in front of the direction it is facing
     - if movement does not cross bounding box of wall, person, or other zombie objects
            - update dumb zombie's location using moveTo() method
            - decrease movement plan distance by 1
     - otherwise, dumb zombie was blocked from moving and set movement plan distance to 0 (causes it to choose a new direction to move during next tick)
     
     
     details:
    - can be damaged by flame
            - sets own state to dead
            - play SOUND_ZOMBIE_DIE
        - increase player's score by 1000
     - 1 in 10 dumb zombies are carrying a vaccine goodie when they die; if it does, it will introduce a new vaccine goodie at its (x, y) coordinate by adding it to the StudentWorld object
     - cannot be infected by vomit
     - blocks other objects from moving nearby/onto it
     - does not block flame
     
     */
}

DumbZombie::~DumbZombie()
{
    
}
