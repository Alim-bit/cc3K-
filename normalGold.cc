#include "normalGold.h"
#include <iostream>

NormalGold::NormalGold(Cell* pos, Floor* fl)
    : Item(pos, fl, 6, 'G') {}

void NormalGold::pickUp() {
    std::cout << "Picked up a Normal Gold pile" << std::endl;
}
