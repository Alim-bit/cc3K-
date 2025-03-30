#include "baPotion.h"
#include <iostream>

BAPotion::BAPotion()
    : Item("BA", 'P', 1) {}

void BAPotion::pickUp() {
    std::cout << "Picked up a Boost Attack Potion" << std::endl;
}
