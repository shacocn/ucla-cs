#ifndef Exit_h
#define Exit_h

#include "StaticActor.h"

class Exit : public StaticActor
{
public:
    Exit(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Exit();
private:
    
};

#endif /* Exit_h */
