#include "merchant.h"

Merchant::Merchant() : Enemy("Merchant", 'M', 30, 30, 70, 5) {}

void Merchant::makeHostile() {
    Merchant::hostile = true;
}

bool Merchant::isHostile() {
    return Merchant::hostile;
}
