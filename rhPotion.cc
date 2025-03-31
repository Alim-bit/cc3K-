#include "rhPotion.h"
#include <iostream>

RHPotion::RHPotion()
    : Item("RH", 'P', 0) {}

bool RHPotion::isKnown() {
    return known;
}

void RHPotion::makeKnown() {
    RHPotion::known = true;
}

