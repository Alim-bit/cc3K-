#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <string>
#include <memory>
#include "item.h"

class Cell; // forward
class Floor; // forward

class ItemFactory {
public:
    static std::unique_ptr<Item> create(const std::string &type, Cell* pos, Floor* fl);
};

#endif // ITEMFACTORY_H
