#ifndef BAPOTION_H
#define BAPOTION_H

#include "item.h"

class BAPotion : public Item {
    inline static bool known = false;
public:
    BAPotion();
    bool isKnown();
    void makeKnown();
};

#endif // BAPOTION_H
