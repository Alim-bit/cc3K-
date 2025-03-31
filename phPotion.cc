#include "phPotion.h"
#include <iostream>

PHPotion::PHPotion()
    : Item("PH", 'P', 3) {}

void PHPotion::pickUp() {
    std::cout << "Picked up a Poison Health Potion" << std::endl;
}

bool PHPotion::isKnown() {
    return known;
}

void PHPotion::makeKnown() {
    PHPotion::known = true;
}
