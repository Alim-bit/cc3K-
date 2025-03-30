#include "smallGold.h"
#include <iostream>

SmallGold::SmallGold(Cell* pos, Floor* fl)
    : Item(pos, fl, 6, 'G') {}

void SmallGold::pickUp() {
    std::cout << "Picked up a Small Gold pile" << std::endl;
}
