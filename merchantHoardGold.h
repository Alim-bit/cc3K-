#ifndef MERCHANTHOARDGOLD_H
#define MERCHANTHOARDGOLD_H

#include "item.h"

class MerchantHoardGold : public Item {
public:
    MerchantHoardGold();
    virtual void pickUp() override;
};

#endif // MERCHANTHOARDGOLD_H
