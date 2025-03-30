#ifndef BAPOTION_H
#define BAPOTION_H

#include "item.h"

class BAPotion : public Item {
public:
    BAPotion(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // BAPOTION_H
