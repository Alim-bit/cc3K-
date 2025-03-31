#include "waPotion.h"
#include <iostream>

WAPotion::WAPotion()
    : Item("WA", 'P', 4) {}

bool WAPotion::isKnown() {
    return known;
}

void WAPotion::makeKnown() {
    WAPotion::known = true;
}

