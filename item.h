#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <memory>

// Forward declarations
class Cell;
class Floor;

class Item {
protected:
    // Non-owning pointers to objects managed elsewhere
    Cell* posn;
    Floor* floor;
    char name;
    int value;
public:
    Item(Cell* pos, Floor* fl, int val, char n);
    virtual ~Item() = default;
    virtual void pickUp() = 0;
    char getName() const;
    int getValue() const;
};

#endif // ITEM_H
