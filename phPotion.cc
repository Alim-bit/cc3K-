#include "phPotion.h"
#include <iostream>

PHPotion::PHPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 3, 'P') {}

void PHPotion::pickUp() {
    std::cout << "Picked up a Poison Health Potion" << std::endl;
}
