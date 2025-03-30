#include "dragonHoardGold.h"
#include <iostream>

DragonHoardGold::DragonHoardGold(Cell* pos, Floor* fl)
    : Item(pos, fl, 9, 'G') {}

void DragonHoardGold::pickUp() {
    std::cout << "Picked up a Dragon Hoard Gold pile" << std::endl;
}
