#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include <string>
#include "item.h"

class Cell; // forward
class Floor; // forward

class ItemFactory {
public:
    static std::shared_ptr<Item> createItem(std::string name);
};

#endif // ITEMFACTORY_H
