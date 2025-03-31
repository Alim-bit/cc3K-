#ifndef WDPOTION_H
#define WDPOTION_H

#include "item.h"

class WDPotion : public Item {
    inline static bool known = false;
public:
    WDPotion();
    bool isKnown();
    void makeKnown();
};

#endif // WDPOTION_H
