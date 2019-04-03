#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <cmath>

using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double x, double y, Direction direction, int depth, bool alive, StudentWorld* world) : GraphObject(imageID, x, y, direction, depth), m_alive(alive), m_studentWorld(world) {}

Actor::~Actor()
{
    
}

//----------------------------------------------------------------------

MovingActor::MovingActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : Actor(imageID, startX, startY, startDirection, depth, alive, world) {}

MovingActor::~MovingActor()
{
    
}

//----------------------------------------------------------------------

Person::Person(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : MovingActor(imageID, startX, startY, startDirection, depth, alive, world), m_infectionCount(0) {}

void Person::beVomitedOnIfAppropriate()
{
    increaseInfection();
    if (infectionCount() >= 500)
    {
        world()->playSound(SOUND_ZOMBIE_BORN);
        introduceZombie(getX(), getY());
        dieByFallOrBurnIfAppropriate();
    }
}

void Person::introduceZombie(double x, double y) const
{
    int randNum = randInt(1, 10);
    if (randNum <= 3)
        world()->addActor(new SmartZombie(x, y, world()));
    else
        world()->addActor(new DumbZombie(x, y, world()));
}

Person::~Person()
{
}

//----------------------------------------------------------------------

Penelope::Penelope(double startX, double startY, StudentWorld* world) : Person(IID_PLAYER, startX, startY, 0, 0, true, world), m_flameCharges(0), m_vaccines(0), m_landmines(0) {}

void Penelope::doSomething()
{
    if (!alive())
        return;
    if (infectionCount() > 0)
        beVomitedOnIfAppropriate();
    
    /* If everything seems okay, handle the user's instructions. */
    handleKeyPress();
}

/* Check if the user pressed a key. If space, deal with flame thrower chargers; if tab, deal with land mines; if enter, deal with vaccines; and if a directional arrow key, then move Penelope if possible. */
void Penelope::handleKeyPress()
{
    int keyPress;
    if (world()->getKey(keyPress))
    {
        switch(keyPress)
        {
            case KEY_PRESS_SPACE:
                handleSpace();
                break;
            case KEY_PRESS_TAB:
                handleTab();
                break;
            case KEY_PRESS_ENTER:
                handleEnter();
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                movePenelope(keyPress, up); break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                movePenelope(keyPress, right); break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                movePenelope(keyPress, down); break;
            case KEY_PRESS_LEFT:
                setDirection(left);
                movePenelope(keyPress, left); break;
            default:
                cerr << "key press error!" << endl;
        }
    }
}

void Penelope::handleSpace()
{
    if (m_flameCharges <= 0)
        return; // no flame thrower charges.
    
    m_flameCharges--;
    world()->playSound(SOUND_PLAYER_FIRE);
    fireFlames(getX(), getY(), getDirection());
}

void Penelope::fireFlames(double x, double y, int dir) const
{
    double newX = x;
    double newY = y;
    
    for (int i = SPRITE_WIDTH; i <= 3 * SPRITE_WIDTH; i += SPRITE_WIDTH)
    {
        switch (dir)
        {
            case 0: // right
                newX = x + i;
                break;
            case 90: // up
                newY = y + i;
                break;
            case 180: // left
                newX = x - i;
                break;
            case 270: // down
                newY = y - i;
                break;
        }
        
        if (world()->isFlameBlockedAt(newX, newY, getX(), getY()))
            continue;
        
        world()->addActor(new Flame(newX, newY, world()));
    }
}

void Penelope::handleTab()
{
    if (m_landmines <= 0)
        return; // no land mines!
    Actor *temp = new Landmine(getX(), getY(), world());
    world()->addActor(temp);
    m_landmines--;
}

void Penelope::handleEnter()
{
    if (m_vaccines <= 0)
        return; // no vaccines!
    clearInfection();
    m_vaccines--;
}

void Penelope::movePenelope(int keyPress, int direction)
{
    double curX = getX();
    double curY = getY();
    switch (direction)
    {
        case up:
            curY += 4;
            break;
        case right:
            curX += 4;
            break;
        case down:
            curY -= 4;
            break;
        case left:
            curX -= 4;
            break;
    }
    if (!world()->isAgentMovementBlockedAt(curX, curY, getX(), getY()))
        moveTo(curX, curY);
}

void Penelope::useExitIfAppropriate()
{
    world()->recordLevelFinishedIfAllCitizensGone();
}

void Penelope::pickUpGoodieIfAppropriate(Goodie *g)
{
    g->pickUp(this);
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_PLAYER_DIE);
}

Penelope::~Penelope()
{
}

//----------------------------------------------------------------------

Citizen::Citizen(double startX, double startY, StudentWorld* world) : Person(IID_CITIZEN, startX, startY, 0, 0, true, world) {
    
}

void Citizen::doSomething()
{
    if (!alive())
        return;
    if (infectionCount() > 0)
        beVomitedOnIfAppropriate();
    
    double x, y, dist;
    bool isThreat = false;
    
    /* If the nearest object is Penelope, then the x, y coordinates will refer to Penelope's x, y coordinates and dist will be distance to Penelope. Otherwise, the x,y coordinates will be those of the nearest zombie and dist will refer to distance to nearest Zombie. */
     world()->locateNearestCitizenTrigger(getX(), getY(), x, y, dist, isThreat);
    
    if ((!isThreat || dist == VIEW_WIDTH) && dist <= 80)
    {
        if (x == getX() && getX() < x && !world()->isAgentMovementBlockedAt(getX() + 2, getY(), getX(), getY()))
        {
            setDirection(up);
            moveTo(getX() + 2, getY());
            return;
        }
        else if (x == getX() && getX() > x && !world()->isAgentMovementBlockedAt(getX() + 2, getY(), getX(), getY()))
        {
            setDirection(down);
            moveTo(getX() - 2, getY());
            return;
        }
        else if (y == getY() && getY() < y && !world()->isAgentMovementBlockedAt(getX(), getY() + 2, getX(), getY()))
        {
            setDirection(right);
            moveTo(getX(), getY() + 2);
            return;
        }
        else if (y == getY() && getY() > y && !world()->isAgentMovementBlockedAt(getX(), getY(), getX(), getY() - 2))
        {
            setDirection(left);
            moveTo(getX(), getY() - 2);
            return;
        }
        else
        {
            /* Get direction that moves citizen closer to Penelope. */
            int xDirection = getDirection();
            int yDirection = getDirection();
            double deltaX = 0;
            double deltaY = 0;
            
            if (getX() < x)
            {
                deltaX = 2;
                xDirection = up;
            }
            else
            {
                deltaX = -2;
                xDirection = down;
            }
            
            if (getY() < y)
            {
                deltaY = 2;
                yDirection = right;
            }
            else
            {
                deltaY = -2;
                yDirection = left;
            }
            
            int finalDir = getDirection();
            if (randInt(0, 1) == 0)
            {
                finalDir = xDirection;
                deltaY = 0;
            }
            else
            {
                finalDir = yDirection;
                deltaX = 0;
            }
            
            if (!world()->isAgentMovementBlockedAt(getX() + deltaX, getY() + deltaY, getX(), getY()))
            {
                setDirection(finalDir);
                moveTo(getX() + deltaX, getY() + deltaY);
                return;
            }
        }
    }
    
    if (isThreat && dist <= 80)
    {
        int farthestDirection = getDirection();
        double newZombieDistance = 0;
        double furthestZombieDistance = dist;
        double zombieX = VIEW_WIDTH, zombieY = VIEW_WIDTH;
        if (!world()->isAgentMovementBlockedAt(getX() + 2, getY(), getX(), getY()))
        {
            world()->locateNearestCitizenThreat(getX() + 2, getY(), zombieX, zombieY, newZombieDistance);
            if (newZombieDistance > furthestZombieDistance)
            {
                furthestZombieDistance = newZombieDistance;
                farthestDirection = up;
            }
        }
        if (!world()->isAgentMovementBlockedAt(getX() - 2, getY(), getX(), getY()))
        {
            world()->locateNearestCitizenThreat(getX() - 2, getY(), zombieX, zombieY, newZombieDistance);
            if (newZombieDistance > furthestZombieDistance)
            {
                furthestZombieDistance = newZombieDistance;
                farthestDirection = down;
            }
        }
        if (!world()->isAgentMovementBlockedAt(getX(), getY() + 2, getX(), getY()))
        {
            world()->locateNearestCitizenThreat(getX(), getY() + 2, zombieX, zombieY, newZombieDistance);
            if (newZombieDistance > furthestZombieDistance)
            {
                furthestZombieDistance = newZombieDistance;
                farthestDirection = right;
            }
        }
        if (!world()->isAgentMovementBlockedAt(getX(), getY() - 2, getX(), getY()))
        {
            world()->locateNearestCitizenThreat(getX(), getY() - 2, zombieX, zombieY, newZombieDistance);
            if (newZombieDistance > furthestZombieDistance)
            {
                furthestZombieDistance = newZombieDistance;
                farthestDirection = left;
            }
        }
        
        if (newZombieDistance == dist)
            return; // nothing we can do!
        
        setDirection(farthestDirection);
        switch (farthestDirection)
        {
            case up:
                if (!world()->isAgentMovementBlockedAt(getX() + 2, getY(), getX(), getY()))
                    moveTo(getX() + 2, getY());
                break;
            case down:
                if (!world()->isAgentMovementBlockedAt(getX() - 2, getY(), getX(), getY()))
                    moveTo(getX() - 2, getY());
                break;
            case right:
                if (!world()->isAgentMovementBlockedAt(getX(), getY() + 2, getX(), getY()))
                    moveTo(getX(), getY() + 2);
                break;
            case left:
                if (!world()->isAgentMovementBlockedAt(getX(), getY() - 2, getX(), getY()))
                    moveTo(getX(), getY() - 2);
                break;
        }
    }
    return;
}

void Citizen::useExitIfAppropriate()
{
    setDead();
    world()->increaseScore(500);
    world()->playSound(SOUND_CITIZEN_SAVED);
    world()->recordCitizenGone();
}

void Citizen::beVomitedOnIfAppropriate()
{
    increaseInfection();
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->recordCitizenGone();
    world()->playSound(SOUND_CITIZEN_DIE);
    world()->increaseScore(-1000);
}

Citizen::~Citizen()
{
     ;
}

//----------------------------------------------------------------------

Zombie::Zombie(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : MovingActor(imageID, startX, startY, startDirection, depth, alive, world), m_movePlanDistance(0) {}

bool Zombie::tryToVomit() const
{
    /* Get the expected vomit coordinates. */
    int playerDirection = getDirection();
    double vomitX = getX();
    double vomitY = getY();
    switch (playerDirection)
    {
        case 0: // right
            vomitX += SPRITE_WIDTH;
            break;
        case 90: // up
            vomitY += SPRITE_WIDTH;
            break;
        case 180: // left
            vomitX -= SPRITE_WIDTH;
            break;
        case 270: // down
            vomitY -= SPRITE_WIDTH;
            break;
    }
    
    /* Check to see if there's a Person near the vomit coordinates. */
    double otherX, otherY, distance;
    world()->locateNearestVomitTrigger(vomitX, vomitX, otherX, otherY, distance);
    
    /* If there are no citizens or Penelope close by, return immediately. */
    if (distance < SPRITE_WIDTH)
        return false;
    
    /* Otherwise, if the Person overlaps with the potential vomit coordinates, create a vomit object at this location. */
    if (world()->overlaps(vomitX, vomitY, otherX, otherY))
    {
        world()->addActor(new Vomit(vomitX, vomitY, world()));
        world()->playSound(SOUND_ZOMBIE_VOMIT);
        return true;
    }
    return false;
}

Zombie::~Zombie()
{
    ;
}

//----------------------------------------------------------------------

DumbZombie::DumbZombie(double startX, double startY, StudentWorld* world) : Zombie(IID_ZOMBIE, startX, startY, 0, 0, true, world) {}

void DumbZombie::doSomething()
{
    if (!alive())
        return;
    
    /* If there is an object in the direction the zombie is facing, then compute zombie coordinates in the direction it's facing. If vomit was successful, return immediately. */
    if (tryToVomit())
        return;
    
    /* Check for a new movement plan. */
    if (movePlanDistance() == 0)
    {
        changeMovePlan(randInt(3, 10));
        int rand = randInt(1, 4);
        switch (rand)
        {
            case 1:
                setDirection(up);
                break;
            case 2:
                setDirection(left);
                break;
            case 3:
                setDirection(right);
                break;
            case 4:
                setDirection(down);
                break;
        }
    }
    
    /* Get destination location. */
    double newX = getX(), newY = getY();
    switch (getDirection())
    {
        case up:
            newY += 1;
            break;
        case right:
            newX += 1;
            break;
        case down:
            newY -= 1;
            break;
        case left:
            newX -= 1;
            break;
    }
    
    if (!world()->isAgentMovementBlockedAt(newX, newY, getX(), getY()))
    {
        moveTo(newX, newY);
        changeMovePlan(movePlanDistance() - 1);
        return;
    }
    
    /* Set movement plan distance to 0. */
    changeMovePlan(0);
}

void DumbZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(1000);
    if (randInt(1, 10) == 1)
    {
        int randNum = randInt(0, 3);
        switch (randNum)
        {
            case 0:
                if (!world()->isAgentMovementBlockedAt(getX() + SPRITE_WIDTH, getY(), getX(), getY()))
                    world()->addActor(new VaccineGoodie(getX() + SPRITE_WIDTH, getY(), world()));
                break;
            case 1:
                if (!world()->isAgentMovementBlockedAt(getX() - SPRITE_WIDTH, getY(), getX(), getY()))
                    world()->addActor(new VaccineGoodie(getX() - SPRITE_WIDTH, getY(), world()));
                break;
            case 2:
                if (!world()->isAgentMovementBlockedAt(getX(), getY() + SPRITE_WIDTH, getX(), getY()))
                    world()->addActor(new VaccineGoodie(getX(), getY() + SPRITE_WIDTH, world()));
                break;
            case 3:
                if (!world()->isAgentMovementBlockedAt(getX(), getY(), getX(), getY() - SPRITE_WIDTH))
                    world()->addActor(new VaccineGoodie(getX(), getY() - SPRITE_WIDTH, world()));
                break;
        }
    }
        world()->addActor(new VaccineGoodie(getX(), getY(), world()));
    
    /*
     When a dumb zombie drops a vaccine goodie, it does not simply drop it at its own (x,y) coordinates, but tries to fling it away instead: It chooses a random direction, computes the coordinates SPRITE_WIDTH units away if the direction is left or right or SPRITE_HEIGHT units away if it is up or down, and if no other object in the game would overlap with an object created at those coordinates, introduces a new vaccine goodie at those coordinates; otherwise, it does not introduce a vaccine object.
     */
}

DumbZombie::~DumbZombie()
{
    ;
}

//----------------------------------------------------------------------

SmartZombie::SmartZombie(double startX, double startY, StudentWorld* world) : Zombie(IID_ZOMBIE, startX, startY, 0, 0, true, world) {}

void SmartZombie::doSomething()
{
    if (!alive())
        return;
    
    /* If there is an object in the direction the zombie is facing, then compute zombie coordinates in the direction it's facing. If vomit was successful, return immediately. */
    if (tryToVomit())
        return;
    
    if (movePlanDistance() == 0)
    {
        changeMovePlan(randInt(3, 10));
        double closestX = getX();
        double closestY = getY();
        double distance;
        world()->locateNearestVomitTrigger(getX(), getY(), closestX, closestY, distance);
        
        if (distance == VIEW_WIDTH || distance > 80)
        {
            int rand = randInt(1, 4);
            switch (rand)
            {
                case 1:
                    setDirection(up);
                    break;
                case 2:
                    setDirection(left);
                    break;
                case 3:
                    setDirection(right);
                    break;
                case 4:
                    setDirection(down);
                    break;
            }
        }
        
        else if (distance <= 80)
        {
            int xDir = down;
            int yDir = left;
            
            if (closestX - getX() > 0)
                xDir = up;
            if (closestY - getY() > 0)
                yDir = right;
            
            if (closestX == getX())
                setDirection(xDir);
            else if (closestY == getY())
                setDirection(yDir);
            else
            {
                if (randInt(0, 1) == 0)
                    setDirection(xDir);
                else
                    setDirection(yDir);
            }
        }
    }
    
    /* Get destination location. */
    double newX = getX(), newY = getY();
    switch (getDirection())
    {
        case up:
            newY += 1;
            break;
        case right:
            newX += 1;
            break;
        case down:
            newY -= 1;
            break;
        case left:
            newX -= 1;
            break;
    }
    
    if (!world()->isAgentMovementBlockedAt(newX, newY,getX(), getY()))
    {
        moveTo(newX, newY);
        changeMovePlan(movePlanDistance() - 1);
        return;
    }
    
    /* Set movement plan distance to 0. */
    changeMovePlan(0);
}

void SmartZombie::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_ZOMBIE_DIE);
    world()->increaseScore(2000);
}

SmartZombie::~SmartZombie()
{
    ;
}

//----------------------------------------------------------------------

StaticActor::StaticActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : Actor(imageID, startX, startY, startDirection, depth, alive, world) {}

StaticActor::~StaticActor()
{
    ;
}

//----------------------------------------------------------------------

Landmine::Landmine(double startX, double startY, StudentWorld* world) : StaticActor(IID_LANDMINE, startX, startY, 0, 1, true, world), m_active(false), m_safetyTicks(30) {}


void Landmine::doSomething()
{
    if (!alive())
        return;
    
    /* Decrement safety ticks if not active yet. */
    if (!m_active)
        m_safetyTicks--;
    if (m_safetyTicks == 0)
    {
        m_active = true;
        return;
    }
}

void Landmine::activateIfAppropriate(Actor *a)
{
    /* If not active or not Penelope, citizen, or zombie, return. */
    if (!a->canMoveAround() || !m_active)
        return;
    
    dieByFallOrBurnIfAppropriate();
}

void Landmine::dieByFallOrBurnIfAppropriate()
{
    setDead();
    world()->playSound(SOUND_LANDMINE_EXPLODE);
    
    /* Add flames at location of landmine and in eight adjacent squares. */
    for (int col = getX() - SPRITE_WIDTH; col <= getX() + SPRITE_WIDTH; col += SPRITE_WIDTH)
    {
        for (int row = getY() - SPRITE_WIDTH; row <= getY() + SPRITE_WIDTH; row += SPRITE_WIDTH)
            world()->addActor(new Flame(col, row, world()));
    }
    
    /* Add a pit in that location. */
    world()->addActor(new Pit(getX(), getY(), world()));
}

Landmine::~Landmine()
{
    
}

//----------------------------------------------------------------------

Projectile::Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : StaticActor(imageID, startX, startY, startDirection, depth, alive, world), m_aliveTicks(0) {}

Projectile::~Projectile()
{
    
}

//----------------------------------------------------------------------

Flame::Flame(double startX, double startY, StudentWorld* world) : Projectile(IID_FLAME, startX, startY, 0, 0, true, world) {}

void Flame::doSomething()
{
    if (!alive())
        return; // do nothing
    incrementAliveTicks();
    if (shouldBeDead())
    { // two ticks; set to dead
        setDead();
    }
}

void Flame::activateIfAppropriate(Actor *a)
{
    if (!a->blocksFlame())
        a->dieByFallOrBurnIfAppropriate();
}

Flame::~Flame()
{
    
}

//----------------------------------------------------------------------

Vomit::Vomit(double startX, double startY, StudentWorld* world) : Projectile(IID_VOMIT, startX, startY, 0, 0, true, world) {}

void Vomit::doSomething()
{
    if (!alive())
        return; // do nothing
    incrementAliveTicks();
    if (shouldBeDead())
    { // two ticks; set to dead
        setDead();
        return;
    }
}

void Vomit::activateIfAppropriate(Actor *a)
{
    if (a->canBeInfected())
        a->beVomitedOnIfAppropriate();
}

Vomit::~Vomit()
{
    
}

//----------------------------------------------------------------------

Pit::Pit(double startX, double startY, StudentWorld* world) : StaticActor(IID_PIT, startX, startY, 0, 0, true, world) {}

void Pit::doSomething()
{
    if (!alive())
        return;
}

void Pit::activateIfAppropriate(Actor *a)
{
    if (a->canMoveAround())
    {
        a->dieByFallOrBurnIfAppropriate();
    }
}

Pit::~Pit()
{
    
}

//----------------------------------------------------------------------

Goodie::Goodie(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world) : StaticActor(imageID, startX, startY, startDirection, depth, alive, world) {}

void Goodie::activateIfAppropriate(Actor* a)
{
    /* Only let Penelope pick up a goodie. */
    if (a->canBeInfected() && a->canTriggerCitizens())
    {
        a->pickUpGoodieIfAppropriate(this);
        world()->increaseScore(50);
        world()->playSound(SOUND_GOT_GOODIE);
        setDead();
    }
}

void Goodie::dieByFallOrBurnIfAppropriate()
{
    setDead();
}

Goodie::~Goodie()
{
    
}

//----------------------------------------------------------------------

GasCanGoodie::GasCanGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_GAS_CAN_GOODIE, startX, startY, 0, 1, true, world) {}


void GasCanGoodie::doSomething()
{
    if (!alive())
        return;
}

void GasCanGoodie::pickUp(Penelope *p)
{
    p->increaseFlameCharges();
}

GasCanGoodie::~GasCanGoodie()
{
    
}

//----------------------------------------------------------------------

VaccineGoodie::VaccineGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_VACCINE_GOODIE, startX, startY, 0, 1, true, world) {}

void VaccineGoodie::doSomething()
{
    if (!alive())
        return;
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

void VaccineGoodie::pickUp(Penelope *p)
{
    p->increaseVaccines();
}


VaccineGoodie::~VaccineGoodie()
{
    
}

//----------------------------------------------------------------------

LandmineGoodie::LandmineGoodie(double startX, double startY, StudentWorld* world) : Goodie(IID_LANDMINE_GOODIE, startX, startY, 0, 1, true, world) {}

void LandmineGoodie::doSomething()
{
    if (!alive())
        return;
}

void LandmineGoodie::pickUp(Penelope *p)
{
    p->increaseLandmines();
}

LandmineGoodie::~LandmineGoodie()
{
    
}

//----------------------------------------------------------------------

Exit::Exit(double startX, double startY, StudentWorld* world) : StaticActor(IID_EXIT, startX, startY, 0, 1, true, world) {}

void Exit::activateIfAppropriate(Actor* a)
{
    a->useExitIfAppropriate();
}

void Exit::doSomething()
{
    if (!alive())
        return;
    /*
     
     - must determine if overlaps with citizen BUT NOT PENELOPE
     - if there is overlap
     - inform the studentworld that the user receives 500 points
     - set citizen object's state to dead BUT must not kill the citizen in a way that deducts points from the player as if the citizen died due to a zombie inf ection, a flame, or a pit
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

//----------------------------------------------------------------------

Wall::Wall(double startX, double startY, StudentWorld* world) : StaticActor(IID_WALL, startX, startY, 0, 0, true, world) {}

void Wall::doSomething()
{
    // do nothing.
}

Wall::~Wall()
{
    
}
