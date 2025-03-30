#include "rhPotion.h"
#include <iostream>

RHPotion::RHPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 0, 'P') {}

void RHPotion::pickUp() {
    std::cout << "Picked up a Restore Health Potion" << std::endl;
}
