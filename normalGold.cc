#include "normalGold.h"
#include <iostream>

NormalGold::NormalGold()
    : Item("NG", 'G', 1) {}

void NormalGold::pickUp() {
    std::cout << "Picked up a Normal Gold pile" << std::endl;
}
