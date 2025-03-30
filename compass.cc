#include "compass.h"
#include <iostream>

Compass::Compass(Cell* pos, Floor* fl)
    : Item(pos, fl, 0, 'C') {}

void Compass::pickUp() {
    std::cout << "Picked up the Compass" << std::endl;
}
