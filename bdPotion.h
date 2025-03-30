#ifndef BDPOTION_H
#define BDPOTION_H

#include "item.h"

class BDPotion : public Item {
public:
    BDPotion(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // BDPOTION_H
