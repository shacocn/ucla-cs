#include "Penelope.h"
#include "StudentWorld.h"
#include <cassert>

using namespace std;

/*
 
 When Penelope is first created:
 - have an ID of IID_PLAYER
 - pass into the GraphObject
 - have start location as specified by data file
 - start location is (SPRITE_WIDTH * level_x, SPRITE_HEIGHT * level_y) where level_x and level_y can be obtained using Level class
 - studentWorld object can pass in this (x, y) location when constructing the object
 - starts out alive
 - boolean alive/dead? same as base class actor
 - direction is right
 - depth is 0
 
 
 - no landmines, flamethrower charges, or vaccines
 - infection status of false
 - infection count of 0
 */
Penelope::Penelope(double startX, double startY, StudentWorld* world) : Person(IID_PLAYER, startX, startY, 0, 0, true, world), m_lives(3), m_flameChargesHeld (0), m_vaccinesHeld (0), m_landminesHeld (0)
{
}

/* ------------------------DONE----------------------------
 
 TO GET DIRECTION:
 - use getKey() from GameWorld class
 - if true, int variable passed to it is set to code for the key
 - else it will return false
 
 
 Hint: Since your Penelope object will need to access the getKey() method in the GameWorld class (which is the base class for your StudentWorld class), your Penelope object (or more likely, one of its base classes) will need a way to obtain a pointer to the StudentWorld object it belongs to. If you look at our code example, you’ll see how Penelope’s doSomething() method first gets a pointer to its world via a call to getWorld() (a method in one of its base classes that returns a pointer to a StudentWorld), and then uses this pointer to call the getKey() method.
 
 
 - example func:
 
 void Penelope::doSomething()
 {
 ...
 int ch;
 if (getWorld()->getKey(ch)) {
 // user hit a key during this tick! switch (ch)
 {
 case KEY_PRESS_LEFT:
 ... move Penelope to the left ...; break;
 case KEY_PRESS_RIGHT:
 ... move Penelope to the right ...; break;
 case KEY_PRESS_SPACE:
 ... add flames in front of Penelope...; break;
 // etc... }
 }
 */
void Penelope::doSomething()
{
    /*
     
     - check to see if she is alive
            - if dead, return immediately
     - check if penelope is infected (vomited on by zombie)
            - if yes, increase infection count by one
            - if infection count >= 500 she becomes a zombie
                    - status is dead
                    - play SOUND_PLAYER_DIE
                    - return immediately
            - StudentWorld object should detect death and current level ends (pass in information somehow... check for alive/dead boolean? return boolean?)
    - check if player pressed a key
        - if space key and penelope has at least one flamethrower charge
                - fire three flames into three slots in front of her
                - flamethrower count decrease by 1
                - play SOUND_PLAYER_FIRE
                - add three new flame objects
            - if penelope is at (px, py) then the flame objets will go: for i = 0, 1, and 2:
                - if facing up, pos = (px, py + i*SPRITE_HEIGHT)
                - if facing down, pos = (px, py - i*SPRITE_HEIGHT)
                - if facing left, pos = (px - i*SPRITE_WIDTH, py)
                - if facing right, pos = (px + i*SPRITE_WIDTH, py)
            - algorithm to add flames:
                - for each i = 0, 1, and 2 slots in front of penny
                        - compute position pos where flame will go
                        - if flame at pos overlaps wall or exit
                                - stop loop
                        - otherwise add new flame object at pos with starting direction that is the same direction penelope is facing
        - if user pressed the tab key and penelope has land mines
                - introduce landmine at current position and decrease landmine count by 1
        - if user pressed enter key and penelope has any vaccines in her inventory, penelope will set infected status to false and reduce vaccine count by 1 (wasted vaccine if not infected meaning decrease count regardless)
        - if up, down, left, or right using directional key
                - set direction to specified movement direction
                - determine penelope's dest location which is 4 pixels in direction penelope is facing
                - if movement doesn't cause bounding box to intersect with bounding box of any wall, citizen, or zombie objets, then update penelope's location to the specified location with moveTo() method
     
    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
     
     OTHER STUFF:
     - if vomit overlaps penelope, infection status becomes true
     - if flame object overlaps penelope, it will kill her
            - set status to dead
            - play SOUND_PLAYER_DIE sound effect
            - level ends (studentworld object detects)
     - blocks other objects from moving nearby/onto her; bounding box should never intersect with citizen, zombie, or wall
     
     |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
     ... }
     
     
     */
    
    if (!isAlive())
        return; // dead penelope :(
    
    int keyPress;
    if (getWorld()->getKey(keyPress))
    {
        switch(keyPress)
        {
            case KEY_PRESS_UP:
                setDirection(up);
                moveTo(getX(), getY()+1);
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                moveTo(getX()+1, getY());
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                moveTo(getX(), getY()-1);
                break;
            case KEY_PRESS_LEFT:
                setDirection(left);
                moveTo(getX()-1, getY());
                break;
            default:
                cerr << "not coded yet" << endl;
        }
    }
    

}

Penelope::~Penelope()
{
    
}
