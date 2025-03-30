#ifndef WDPOTION_H
#define WDPOTION_H

#include "item.h"

class WDPotion : public Item {
public:
    WDPotion();
    virtual void pickUp() override;
};

#endif // WDPOTION_H
