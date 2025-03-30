#include "rhPotion.h"
#include <iostream>

RHPotion::RHPotion()
    : Item("RH", 'P', 0) {}

void RHPotion::pickUp() {
    std::cout << "Picked up a Restore Health Potion" << std::endl;
}
