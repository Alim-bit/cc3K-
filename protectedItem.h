#ifndef PROTECTEDITEM_H
#define PROTECTEDITEM_H

#include "item.h"
#include <memory>

// Forward declaration for Enemy
class Enemy;

class ProtectedItem : public Item {
private:
    // Own the contained item using a unique_ptr
    std::unique_ptr<Item> item;
    // Use a shared_ptr for the protector (assumed managed elsewhere)
    std::shared_ptr<Enemy> protector;
public:
    ProtectedItem(std::unique_ptr<Item> itm, std::shared_ptr<Enemy> prot);
    virtual ~ProtectedItem() = default;
    virtual void pickUp() override;
};

#endif // PROTECTEDITEM_H
