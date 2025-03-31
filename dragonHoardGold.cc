#include "dragonHoardGold.h"
#include <iostream>

DragonHoardGold::DragonHoardGold()
    : Item("DH", 'G', 6) {}

void DragonHoardGold::pickUp() {
    std::cout << "Picked up a Dragon Hoard Gold pile" << std::endl;
}
