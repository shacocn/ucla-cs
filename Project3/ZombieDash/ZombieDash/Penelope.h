#ifndef Penelope_h
#define Penelope_h

#include "Person.h"

class Penelope: public Person
{
public:
    Penelope(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Penelope();
private:
    int m_lives;
    int m_flameChargesHeld;
    int m_vaccinesHeld;
    int m_landminesHeld;
};

#endif /* Penelope_h */
