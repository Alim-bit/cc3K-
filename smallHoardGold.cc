#include "smallHoardGold.h"
#include <iostream>

SmallHoardGold::SmallHoardGold()
    : Item("SH", 'G', 7) {}

void SmallHoardGold::pickUp() {
    std::cout << "Picked up a Small Hoard Gold pile" << std::endl;
}
