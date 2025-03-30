#include "bdPotion.h"
#include <iostream>

BDPotion::BDPotion()
    : Item("BD", 'P', 2) {}

void BDPotion::pickUp() {
    std::cout << "Picked up a Boost Defense Potion" << std::endl;
}
