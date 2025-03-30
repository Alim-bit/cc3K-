#include "bdPotion.h"
#include <iostream>

BDPotion::BDPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 2, 'P') {}

void BDPotion::pickUp() {
    std::cout << "Picked up a Boost Defense Potion" << std::endl;
}
