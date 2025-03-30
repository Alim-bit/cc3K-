#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H

#include "item.h"

class BarrierSuit : public Item {
public:
    BarrierSuit();
    virtual void pickUp() override;
};

#endif // BARRIERSUIT_H
