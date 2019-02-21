#ifndef VaccineGoodie_h
#define VaccineGoodie_h

#include "Goodie.h"

class VaccineGoodie : public Goodie
{
public:
    VaccineGoodie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~VaccineGoodie();
};

#endif /* VaccineGoodie_h */
