#ifndef LandmineGoodie_h
#define LandmineGoodie_h

#include "Goodie.h"

class LandmineGoodie : public Goodie
{
public:
    LandmineGoodie(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~LandmineGoodie();
private:
};

#endif /* LandmineGoodie_h */
