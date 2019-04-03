#ifndef Actor_h
#define Actor_h

#include "GraphObject.h"

class StudentWorld;
class Goodie;

class Actor : public GraphObject
{
public:
    Actor(int imageID, double x, double y, Direction direction, int depth, bool alive, StudentWorld* world);
    virtual void doSomething() = 0;
    virtual ~Actor();
    
    /* Accessor functions. */
    bool alive() const { return m_alive; };
    StudentWorld* world() const { return m_studentWorld; };
    
    /* Mutator functions. */
    void setDead() { m_alive = false; };
    
    /* Descriptor functions. */
    virtual bool blocksFlame() const { return false; }; // Exit/Wall
    virtual bool blocksMovement() const { return false; }; // Wall/MovingActors
    virtual bool canBeInfected() const { return false; }; // Penny/Citizen
    virtual bool canMoveAround() const { return false; }; // MovingActors
    virtual bool canTriggerCitizens() const { return false; }; // Penny/Zombies
    
    // If this is an activated object, perform its effect on a (e.g., for an
    // Exit have a use the exit).
    virtual void activateIfAppropriate(Actor* a) {};
    virtual void useExitIfAppropriate() {};
    virtual void dieByFallOrBurnIfAppropriate() {};
    virtual void beVomitedOnIfAppropriate() {};
    virtual void pickUpGoodieIfAppropriate(Goodie* g) {};
    
private:
    /* Private data members. */
    bool m_alive;
    StudentWorld* m_studentWorld;
};

//----------------------------------------------------------------------

class MovingActor : public Actor
{
public:
    MovingActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual ~MovingActor();
    
    /* Mutator functions. */
    virtual bool canMoveAround() const { return true; };
    virtual bool blocksMovement() const { return true; };
private:
};

//-----------------------------------------------------------------------

class Person : public MovingActor
{
public:
    Person(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual ~Person();
    
    /* Accessor functions. */
    void clearInfection() { m_infectionCount = 0; };
    int infectionCount() const { return m_infectionCount; };
    void increaseInfection() { m_infectionCount++; };
    
    /* Mutator functions. */
    virtual void beVomitedOnIfAppropriate();
    
    /* Descriptor functions. */
    virtual bool canBeInfected() const { return true; };
    
private:
    int m_infectionCount;
    
    /* Private member functions. */
    void introduceZombie(double x, double y) const;
};

//-----------------------------------------------------------------------

class Penelope: public Person
{
public:
    Penelope(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Penelope();
    
    /* Mutator functions. */
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    
    /* Descriptor functions. */
    virtual bool canTriggerCitizens() const { return true; };
    virtual void pickUpGoodieIfAppropriate(Goodie* g);
    
    /* Accessor functions. */
    int numFlameCharges() const { return m_flameCharges; };
    int numVaccines() const { return m_vaccines; };
    int numLandminesHeld() const { return m_landmines; };
    void increaseFlameCharges() { m_flameCharges += 5; };
    void increaseVaccines() { m_vaccines++; };
    void increaseLandmines() { m_landmines += 2; };
    
private:
    int m_flameCharges;
    int m_vaccines;
    int m_landmines;
    
    /* Private member functions. */
    void handleInfection();
    void handleKeyPress();
    void handleSpace();
    void handleTab();
    void handleEnter();
    void movePenelope(int keyPress, int direction);
    void fireFlames(double x, double y, int dir) const;
};

//-----------------------------------------------------------------------

class Citizen : public Person
{
public:
    Citizen(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Citizen();
    
    /* Mutator functions. */
    virtual void useExitIfAppropriate();
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void beVomitedOnIfAppropriate();
    virtual bool frozenOnEvenTick() const { return true; };
};

//-----------------------------------------------------------------------

class Zombie : public MovingActor
{
public:
    Zombie(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual ~Zombie();
    
    /* Accessor functions. */
    int movePlanDistance() const { return m_movePlanDistance; };
    void changeMovePlan(int change) { m_movePlanDistance = change; };
    bool tryToVomit() const;
    
    /* Descriptor functions. */
    virtual bool frozenOnEvenTick() const { return true; };
    virtual bool canTriggerCitizens() const { return true; };
    
private:
    /* Private data members. */
    int m_movePlanDistance;
};

//-----------------------------------------------------------------------

class DumbZombie : public Zombie
{
public:
    DumbZombie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~DumbZombie();
    
    /* Mutator functions. */
    virtual void dieByFallOrBurnIfAppropriate();
    
private:
    /* Private member functions. */
    void dropGoodie() const;
};

//-----------------------------------------------------------------------

class SmartZombie : public Zombie
{
public:
    SmartZombie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~SmartZombie();
    
    /* Mutator functions. */
    virtual void dieByFallOrBurnIfAppropriate();
};

//-----------------------------------------------------------------------

class StaticActor : public Actor
{
public:
    StaticActor(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    virtual ~StaticActor();
};

//-----------------------------------------------------------------------

class Landmine : public StaticActor
{
public:
    Landmine(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    ~Landmine();
    
    /* Accessor functions. */
    bool isActive() const { return m_active; };
    
    /* Mutator functions. */
    void setActiveState(bool newStatus) { m_active = newStatus; };
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void activateIfAppropriate(Actor* a);
    
private:
    /* Private data members. */
    bool m_active;
    int m_safetyTicks;
};

//-----------------------------------------------------------------------

class Projectile : public StaticActor
{
public:
    Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    ~Projectile();
    
    /* Descriptor functions. */
    bool shouldBeDead() const { return m_aliveTicks == 2; };
    void incrementAliveTicks() { m_aliveTicks++; };
private:
    int m_aliveTicks;
};

//-----------------------------------------------------------------------

class Flame : public Projectile
{
public:
    Flame(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Flame();
    
    /* Mutator functions. */
    virtual void activateIfAppropriate(Actor *a);
};

//-----------------------------------------------------------------------

class Vomit : public Projectile
{
public:
    Vomit(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Vomit();
    
    /* Mutator functions. */
    virtual void activateIfAppropriate(Actor *a);
};

//-----------------------------------------------------------------------

class Pit : public StaticActor
{
public:
    Pit(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Pit();
    
    /* Descriptor functions. */
    virtual void activateIfAppropriate(Actor *a);
};

//-----------------------------------------------------------------------

class Goodie : public StaticActor
{
public:
    Goodie(int imageID, int startX, int startY, Direction startDirection, int depth, bool alive, StudentWorld* world);
    ~Goodie();
    
    /* Mutator functions. */
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
    virtual void pickUp(Penelope *p) = 0;
};

//-----------------------------------------------------------------------

class GasCanGoodie : public Goodie
{
public:
    GasCanGoodie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~GasCanGoodie();
    
    /* Mutator functions. */
    virtual void pickUp(Penelope *p);
};

//-----------------------------------------------------------------------

class VaccineGoodie : public Goodie
{
public:
    VaccineGoodie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~VaccineGoodie();
    
    /* Mutator functions. */
    virtual void pickUp(Penelope *p);
};

//-----------------------------------------------------------------------

class LandmineGoodie : public Goodie
{
public:
    LandmineGoodie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~LandmineGoodie();
    
    /* Mutator functions. */
    virtual void pickUp(Penelope *p);
};

//-----------------------------------------------------------------------

class Exit : public StaticActor
{
public:
    Exit(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Exit();
    
    /* Descriptor functions. */
    virtual bool blocksFlame() const { return true; };
    virtual void activateIfAppropriate(Actor* a);
    
};

//-----------------------------------------------------------------------

class Wall : public StaticActor
{
public:
    Wall(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Wall();
    
    /* Descriptor functions. */
    virtual bool blocksFlame() const { return true; };
    virtual bool blocksMovement() const { return true; };
};

//-----------------------------------------------------------------------

#endif
