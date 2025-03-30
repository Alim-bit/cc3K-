#ifndef WDPOTION_H
#define WDPOTION_H

#include "item.h"

class WDPotion : public Item {
public:
    WDPotion(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // WDPOTION_H
