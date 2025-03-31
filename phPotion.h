#ifndef PHPOTION_H
#define PHPOTION_H

#include "item.h"

class PHPotion : public Item {
    inline static bool known = false;
public:
    PHPotion();
    bool isKnown();
    void makeKnown();
};

#endif // PHPOTION_H
