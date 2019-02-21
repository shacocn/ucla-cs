#ifndef Penelope_h
#define Penelope_h

#include "Person.h"

class Penelope: public Person
{
public:
    Penelope(double startX, double startY);
    virtual void doSomething();
    virtual ~Penelope();
private:
    // lives (starts with 3)
    // flamethrower charges (starts with 0)
    // vaccines held (starts with 0)
    // landmines held (starts with 0)
};

#endif /* Penelope_h */
