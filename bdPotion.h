#ifndef BDPOTION_H
#define BDPOTION_H

#include "item.h"

class BDPotion : public Item {
    inline static bool known = false;
public:
    BDPotion();
    virtual void pickUp() override;
    bool isKnown();
    void makeKnown();
};

#endif // BDPOTION_H
