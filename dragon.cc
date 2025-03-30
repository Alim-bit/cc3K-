#include "dragon.h"

Dragon::Dragon() : Enemy("Dragon", 'D', 150, 150, 20, 20) {}

void Dragon::resetHostile() {
    hostile = false;
}

void Dragon::makeHostile() {
    hostile = true;
}

bool Dragon::isHostile() {
    return hostile;
}
