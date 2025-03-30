#include "waPotion.h"
#include <iostream>

WAPotion::WAPotion()
    : Item("WA", 'P', 4) {}

void WAPotion::pickUp() {
    std::cout << "Picked up a Wound Attack Potion" << std::endl;
}
