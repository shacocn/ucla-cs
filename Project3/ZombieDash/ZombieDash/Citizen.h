#ifndef Citizen_h
#define Citizen_h

#include "Person.h"

class Citizen : public Person
{
public:
    Citizen(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Citizen();
private:
};

#endif /* Citizen_h */
