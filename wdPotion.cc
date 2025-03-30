#include "wdPotion.h"
#include <iostream>

WDPotion::WDPotion(Cell* pos, Floor* fl)
    : Item(pos, fl, 5, 'P') {}

void WDPotion::pickUp() {
    std::cout << "Picked up a Wound Defense Potion" << std::endl;
}
