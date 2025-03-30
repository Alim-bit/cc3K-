#ifndef PHPOTION_H
#define PHPOTION_H

#include "item.h"

class PHPotion : public Item {
public:
    PHPotion(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // PHPOTION_H
