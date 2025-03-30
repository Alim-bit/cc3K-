#include "item.h"
#include <string>

using namespace std;

Item::Item( string name, char symbol, int value)
    : name{name}, symbol{symbol}, value{value}, x{0}, y{0} {}

string Item::getName() const { return name; }

char Item::getSymbol() const { return symbol; }

int Item::getValue() const { return value; }

int Item::getX() const { return x; }

int Item::getY() const { return y; }

void Item::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}
