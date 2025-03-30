#include "compass.h"
#include <iostream>

Compass::Compass()
    : Item("C", 'C', 10) {}

void Compass::pickUp() {
    std::cout << "Picked up the Compass" << std::endl;
}
