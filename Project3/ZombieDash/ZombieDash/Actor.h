#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int imageID, double x, double y, Direction direction, int depth, bool alive, StudentWorld* world);
    virtual void doSomething();
    virtual ~Actor();
    
    /* Accessor functions. */
    bool isAlive() const { return m_alive; };
    StudentWorld* getWorld() const { return m_studentWorld; };
    
    /* Mutator functions. */
    void setLifeStatus(bool newStatus) { m_alive = newStatus; };
    bool overlaps(const Actor* other) const;
    
private:
    /* Private data members. */
    bool m_alive;
    StudentWorld* m_studentWorld;
    
    /* Private member functions. */
    double distanceAwayFrom(const Actor* other) const;
};

#endif // ACTOR_H_
