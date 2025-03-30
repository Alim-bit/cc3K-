#ifndef SMALLHOARDGOLD_H
#define SMALLHOARDGOLD_H

#include "item.h"

class SmallHoardGold : public Item {
public:
    SmallHoardGold(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // SMALLHOARDGOLD_H
