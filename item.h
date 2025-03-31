#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <memory>


class Item {
protected:
    std::string name;
    char symbol;

    int value;
    int x, y;

public:
    Item(std::string name, char symbol, int value);
    virtual ~Item() = default;
    virtual void pickUp() = 0;
    std::string getName() const;
    char getSymbol() const;
    int getValue() const;
    int getX() const;
    int getY() const;
    void setPos(int newX, int newY);

    // for potions
    virtual bool isKnown();
    virtual void makeKnown();
};

#endif // ITEM_H
