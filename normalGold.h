#ifndef NORMALGOLD_H
#define NORMALGOLD_H

#include "item.h"

class NormalGold : public Item {
public:
    NormalGold(Cell* pos, Floor* fl);
    virtual void pickUp() override;
};

#endif // NORMALGOLD_H
