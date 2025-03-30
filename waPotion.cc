#include "waPotion.h"
#include <iostream>

WAPotion::WAPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 4, 'P') {}

void WAPotion::pickUp() {
    std::cout << "Picked up a Wound Attack Potion" << std::endl;
}
