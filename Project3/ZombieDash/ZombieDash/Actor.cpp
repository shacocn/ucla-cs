#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double x, double y, Direction direction, int depth) : GraphObject(imageID, x, y, direction, depth)
{
    /*
     Can only use these methods from GraphObject (very helpful though)
     
     1. GraphObject(int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
     - x value ranges from 0 to VIEW_WIDTH-1 inclusive and y values from from 0 to VIEW_HEIGHT-1 inclusive
     - coordinates are passed in (column, row) not (row, column)
     - greater depth means drawn in the background and get covered up by objects with lower depth
     - imageID value
     IID_PLAYER (for Penelope)
     IID_ZOMBIE (for both smart and dumb zombies) IID_CITIZEN
     IID_FLAME
     IID_VOMIT
     IID_PIT
     IID_LANDMINE (for a deployed landmine) IID_VACCINE_GOODIE
     IID_GAS_CAN_GOODIE
     IID_LANDMINE_GOODIE
     IID_EXIT
     IID_WALL
     - NOTE: DO NOT STORE THE IMAGE ID!!!
     2. double getX() const;
     3. double getY() const;
     4. virtual void moveTo(double x, double y);
     - moveTo(getX()-1, y); moves one pixel to the left
     - note that parameters is x, y (col, row)
     5. int getDirection() const;
     - returns up, down, left, or right
     6. void setDirection(Direction d);
     */
}

void Actor::doSomething()
{
    /*

     1. if an actor died earlier in the current tick, then the dead actor must not have a chance to do something during the current tick
     2. live actors must not interact with an actor after it has died
            - dead zombie cannot block person moving into a location that intersects with its former bounding box
     3. if f key is pressed, game controller stops calling move() every tick and move() is called when a key is pressed (except r)
            - press r to resume regular gameplay

     */
}

Actor::~Actor()
{
    
}
