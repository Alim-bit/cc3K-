#ifndef NORMALGOLD_H
#define NORMALGOLD_H

#include "item.h"

class NormalGold : public Item {
public:
    NormalGold();
    virtual void pickUp() override;
};

#endif // NORMALGOLD_H
