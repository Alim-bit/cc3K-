#ifndef WAPOTION_H
#define WAPOTION_H

#include "item.h"

class WAPotion : public Item {
public:
    WAPotion();
    virtual void pickUp() override;
};

#endif // WAPOTION_H
