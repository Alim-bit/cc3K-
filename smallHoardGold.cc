#include "smallHoardGold.h"
#include <iostream>

SmallHoardGold::SmallHoardGold(Cell* pos, Floor* fl)
    : Item(pos, fl, 7, 'G') {}

void SmallHoardGold::pickUp() {
    std::cout << "Picked up a Small Hoard Gold pile" << std::endl;
}
