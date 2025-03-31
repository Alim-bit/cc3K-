#ifndef RHPOTION_H
#define RHPOTION_H

#include "item.h"

class RHPotion : public Item {
    inline static bool known = false;
public:
    RHPotion();
    virtual void pickUp() override;
    bool isKnown();
    void makeKnown();
};

#endif // RHPOTION_H
