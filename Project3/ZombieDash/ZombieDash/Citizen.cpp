#include "Citizen.h"

Citizen::Citizen(double startX, double startY, StudentWorld* world) : Person(IID_CITIZEN, startX, startY, 0, 0, true, world)
{
    /*
     
     x same image id
     x same starting location
     x same starting direction
     x same depth
     
     infection status of false
     infection count of 0
     citizen starts out alive
     
     */
}

void Citizen::doSomething()
{
    /*
     
     - check to see if it's alive; return false if not
     - if infected by vomit it increases infection count by one; if reaches 500, then:
            - set state to dead and play SOUND_ZOMBIE_BORN sound effect
            - decrease player score by 1000
            - introduce new zombie object in same coordinate as former citizen by adding it to the student world object (70% chance that dumb zombie object will introduce and 30% chance a smart zombie object will be introduced)
            - return immediately
     - paralyzed every even tick
     - determine to penelope
     - determine distance to nearest zombie
     - if dist_p < dist-Z or no zombies exist in the level and the citizens euclidean distance from penleope is less than or equal to 80px (so every citizen wants to follow penelope)
            - if citizen is in same row or column as penelope
                    - if citzen can move 2px in direction toward penelope without being blocked (by another citizen, penelope, a zombie, or a wall) citizen will
                                - set direction to be facing toward penelope, move 2 px in that direction using moveTo() method, and immediately return
                                - otherwise skip to #7. blocked!!
            - not in same row: determine one horizontal and one vertical direction that gets citizen closer to penelope, then:
                    - choose one of two directions at random; if canMove2pxInDirection without being blocked by same conditions above, then set direction to that direction, move 2px in that direction, and return
                    - if blcoked in that direction, choose the other of the two and do the same check. if blocked in that direction as well, continue to step 7
     - if there is a zombie whose euclidean distance from the citizen is less than or equal to 80px, citizen wants to run away so
            - for each of the four directions citizen must determine if the citizen is blocked from moving 2px in that direction; if blocked, then ignore that direction otherwise determine distance to nearest zombie of any type if it were to move to this new location
            - if none of the movement options would allow the citizen to get further away (gets closer to another zombie) then return; no better place
            - otherwise, set direction to one that takes it furthest away, move 2 pixels in that direction, return immediatley and do nothing more during tick
     - at this point, no zombies who distance is less than or equal to 80 px; do nothing and return
     
     
     
     details:
     - can be damaged by flame
     - if a flame overlaps with a citizen, it will kill citizen so set state to dead play sound effect and decrease player's score by 1000 points
     - can be infected by vomit
            - set infection status to true if so
     - blocks other objs from moving onto it
     - does not block flames
     
     
     */
}

Citizen::~Citizen()
{
    
}
