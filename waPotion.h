#ifndef WAPOTION_H
#define WAPOTION_H

#include "item.h"

class WAPotion : public Item {
    inline static bool known = false;
public:
    WAPotion();
    virtual void pickUp() override;
    bool isKnown();
    void makeKnown();
};

#endif // WAPOTION_H
