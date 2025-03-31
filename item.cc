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

bool Item::isKnown() { return true; }

// Intentionally empty for non-potion items
void Item::makeKnown() {  }

bool Item::isProtected() {
    return protect;
}

void Item::setProtected(bool b) {
    protect = b;
}

int Item::getEnemyX() {
    return enemyX;
}

int Item::getEnemyY() {
    return enemyY;
}

void Item::setEnemyPos(int newX, int newY) {
    enemyX = newX;
    enemyY = newY;
}
