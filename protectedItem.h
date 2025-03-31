#ifndef PROTECTEDITEM_H
#define PROTECTEDITEM_H

#include "item.h"
#include <memory>

// Forward declaration of Enemy so we can store a pointer
class Enemy;

class ProtectedItem : public Item {
private:
    // The actual item (e.g. a Dragon Hoard Gold)
    std::shared_ptr<Item> item;
    // The enemy protecting this item (e.g. the Dragon)
    std::shared_ptr<Enemy> protector;
public:
    // Constructor: takes the underlying item and its protector
    ProtectedItem(std::shared_ptr<Item> itm, std::shared_ptr<Enemy> prot)
        : Item(itm->getName(), itm->getSymbol(), itm->getValue()),
          item(itm), protector(prot) {}

    // Override the pickUp method
    virtual void pickUp() override;
};

#endif // PROTECTEDITEM_H
