#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor : public GraphObject
{
public:
    Actor(int imageID, double x, double y, Direction direction, int depth);
    virtual void doSomething();
    virtual ~Actor(); 
private:
};

#endif // ACTOR_H_
