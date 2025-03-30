#include "barrierSuit.h"
#include <iostream>

BarrierSuit::BarrierSuit()
    : Item("BS", 'B', 11) {}

void BarrierSuit::pickUp() {
    std::cout << "Picked up the Barrier Suit" << std::endl;
}
