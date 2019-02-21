#include "Landmine.h"

Landmine::Landmine(double startX, double startY) : Weapon(IID_LANDMINE, startX, startY, 0, 1)
{
    /*
     
     regular image ID
     location specified when constructed
     same direction
     DEPTH is 1
     
     
     starts with 30 safety ticks before it becomes active
     starts with inactive state
     starts alive
     
     */
}


void Landmine::doSomething()
{
    /*
     
     - int numberSafetyTicks
     - get's incremented regardless every tick
     - boolean isActive
     - include function triggerMine() ?? activited by both moving actor or flame??
     
     check to see if is currently alive; return immediately if not
     
     if not active yet
        decrement number of safety ticks
        if safety ticks is 0, become active and return
     determine if overlaps with penelope, citizen, or zombie
     if yes:
        set state to dead
        play sound effect SOUND_LANDMINE_EXPLODE
        introduce flame object at same loc
        introduce flame objects in eight adjacent slots around the landmine
        introduce pit object at same loc
     
     
     details:
     can be damaged by flame
     triggers landmine same if flame overlaps
     if damaged:
        set state to dead
        play sound effect to indicate landmine exploded
        infroduce flame object in same loc as landmine
        introduce flame objects in eight adjacent slots
        introduce pit at the same location
     cannot be infected by vomit
     does not block other objects from moving nearby onto them
     does not block flames
     
     */
}

Landmine::~Landmine()
{
    
}
