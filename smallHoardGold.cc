#include "smallHoardGold.h"
#include <iostream>

SmallHoardGold::SmallHoardGold()
    : Item("SH", 'G', 2) {}

void SmallHoardGold::pickUp() {
    std::cout << "Picked up a Small Hoard Gold pile" << std::endl;
}
