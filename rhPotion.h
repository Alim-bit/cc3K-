#ifndef RHPOTION_H
#define RHPOTION_H

#include "item.h"

class RHPotion : public Item {
public:
    RHPotion();
    virtual void pickUp() override;
};

#endif // RHPOTION_H
