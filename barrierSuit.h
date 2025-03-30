#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H

#include "item.h"

class BarrierSuit : public Item {
public:
    BarrierSuit(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // BARRIERSUIT_H
