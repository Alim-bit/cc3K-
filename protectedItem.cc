#include "protectedItem.h"
#include "enemy.h" // so we can call protector->getHP() and getName()
#include <iostream>

void ProtectedItem::pickUp() {
    // If the protector is still alive, block pickup.
    if (protector && protector->getHP() > 0) {
        std::cout << "The " << item->getName() 
                  << " is protected by " << protector->getName() 
                  << ". Defeat it to pick up the item!" << std::endl;
        return;
    }
    // Otherwise, delegate to the underlying item’s pickUp method.
    item->pickUp();
}
