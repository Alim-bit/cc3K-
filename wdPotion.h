#ifndef WDPOTION_H
#define WDPOTION_H

#include "item.h"

class WDPotion : public Item {
    inline static bool known = false;
public:
    WDPotion();
    virtual void pickUp() override;
    bool isKnown();
    void makeKnown();
};

#endif // WDPOTION_H
