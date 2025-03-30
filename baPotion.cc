#include "baPotion.h"
#include <iostream>

BAPotion::BAPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 1, 'P') {}

void BAPotion::pickUp() {
    std::cout << "Picked up a Boost Attack Potion" << std::endl;
}
