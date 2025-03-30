#include "item.h"

Item::Item(Cell* pos, Floor* fl, int val, char n)
    : posn(pos), floor(fl), value(val), name(n) {}

char Item::getName() const { return name; }
int Item::getValue() const { return value; }
