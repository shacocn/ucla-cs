#ifndef Vomit_h
#define Vomit_h

#include "Projectile.h"

class Vomit : public Projectile
{
public:
    Vomit(double startX, double startY);
    virtual void doSomething();
    virtual ~Vomit();
};

#endif /* Vomit_h */
