#include "rhPotion.h"
#include <iostream>

RHPotion::RHPotion()
    : Item("RH", 'P', 0) {}

bool RHPotion::isKnown() {
    return known;
}

bool RHPotion::makeKnown() {
    RHPotion::known = true;
}

