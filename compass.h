#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"

class Compass : public Item {
public:
    Compass(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // COMPASS_H
