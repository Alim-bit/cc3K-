#include "baPotion.h"
#include <iostream>

BAPotion::BAPotion()
    : Item("BA", 'P', 1) {}

void BAPotion::pickUp() {
    std::cout << "Picked up a Boost Attack Potion" << std::endl;
}

bool BAPotion::isKnown() {
    return known;
}

void BAPotion::makeKnown() {
    BAPotion::known = true;
}
