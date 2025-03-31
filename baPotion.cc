#include "baPotion.h"
#include <iostream>

BAPotion::BAPotion()
    : Item("BA", 'P', 1) {}


bool BAPotion::isKnown() {
    return known;
}

void BAPotion::makeKnown() {
    BAPotion::known = true;
}
