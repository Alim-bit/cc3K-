#include "bdPotion.h"
#include <iostream>

BDPotion::BDPotion()
    : Item("BD", 'P', 2) {}

bool BDPotion::isKnown() {
    return known;
}

void BDPotion::makeKnown() {
    BDPotion::known = true;
}

