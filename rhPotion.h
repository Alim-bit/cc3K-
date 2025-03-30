#ifndef RHPOTION_H
#define RHPOTION_H

#include "item.h"

class RHPotion : public Item {
public:
    RHPotion(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // RHPOTION_H
