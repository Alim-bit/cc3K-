#include "wdPotion.h"
#include <iostream>

WDPotion::WDPotion()
    : Item("WD", 'P', 5) {}

bool WDPotion::isKnown() {
    return known;
}

void WDPotion::makeKnown() {
    WDPotion::known = true;
}
