#include "protectedItem.h"
#include "enemy.h"
#include <iostream>

ProtectedItem::ProtectedItem(std::unique_ptr<Item> itm, std::shared_ptr<Enemy> prot)
    : Item(nullptr, nullptr, itm->getValue(), itm->getName()),
      item(std::move(itm)),
      protector(prot) {}

void ProtectedItem::pickUp() {
    // In a full implementation, check if the protector is defeated
    std::cout << "Attempting to pick up a protected item." << std::endl;
    item->pickUp();
}
