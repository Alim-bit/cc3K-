#include "phPotion.h"
#include <iostream>

PHPotion::PHPotion()
    : Item("PH", 'P', 3) {}


bool PHPotion::isKnown() {
    return known;
}

void PHPotion::makeKnown() {
    PHPotion::known = true;
}

