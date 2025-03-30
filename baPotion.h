#ifndef BAPOTION_H
#define BAPOTION_H

#include "item.h"

class BAPotion : public Item {

public:
    BAPotion();
    virtual void pickUp() override;
};

#endif // BAPOTION_H
