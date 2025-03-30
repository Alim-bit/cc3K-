#ifndef DRAGONHOARDGOLD_H
#define DRAGONHOARDGOLD_H

#include "item.h"

class DragonHoardGold : public Item {
public:
    DragonHoardGold(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // DRAGONHOARDGOLD_H
