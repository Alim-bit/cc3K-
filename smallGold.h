#ifndef SMALLGOLD_H
#define SMALLGOLD_H

#include "item.h"

class SmallGold : public Item {
public:
    SmallGold(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // SMALLGOLD_H
