#ifndef GasCanGoodie_h
#define GasCanGoodie_h

#include "Goodie.h"

class GasCanGoodie : public Goodie
{
public:
    GasCanGoodie(double startX, double startY);
    virtual void doSomething();
    virtual ~GasCanGoodie();
private:
};

#endif /* GasCanGoodie_h */
