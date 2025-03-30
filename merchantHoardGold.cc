#include "merchantHoardGold.h"
#include <iostream>

MerchantHoardGold::MerchantHoardGold(Cell* pos, Floor* fl)
    : Item(pos, fl, 8, 'G') {}

void MerchantHoardGold::pickUp() {
    std::cout << "Picked up a Merchant Hoard Gold pile" << std::endl;
}
