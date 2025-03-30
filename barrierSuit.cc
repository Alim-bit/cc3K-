#include "barrierSuit.h"
#include <iostream>

BarrierSuit::BarrierSuit(Cell* pos, Floor* fl)
    : Item(pos, fl, 0, 'B') {}

void BarrierSuit::pickUp() {
    std::cout << "Picked up the Barrier Suit" << std::endl;
}
