#include "merchantHoardGold.h"
#include <iostream>

MerchantHoardGold::MerchantHoardGold()
    : Item("MH", 'G', 4) {}

void MerchantHoardGold::pickUp() {
    std::cout << "Picked up a Merchant Hoard Gold pile" << std::endl;
}
