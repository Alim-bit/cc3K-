#include "wdPotion.h"
#include <iostream>

WDPotion::WDPotion()
    : Item("WD", 'P', 5) {}

void WDPotion::pickUp() {
    std::cout << "Picked up a Wound Defense Potion" << std::endl;
}

bool WDPotion::isKnown() {
    return known;
}

void WDPotion::makeKnown() {
    WDPotion::known = true;
}
