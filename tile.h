#ifndef TILE_H
#define TILE_H

#include <string>
#include <memory>
#include "enemy.h"
#include "item.h"

class Tile {

public:
    enum Type {
        WS, VWALL, HWALL, PASSAGE, DOOR, STAIRS, EMPTY, PLAYER, ENEMY, ITEM
    };

protected:
    // a tile can be any of:
    // whitespace, vWall (Vertical), hWall (Horizontal), passage, door, stairs, empty or
    // "thing": player, enemy or item.

    Type type;
    std::shared_ptr<Enemy> enemy;
    std::shared_ptr<Item> item;

    int x, y;
    bool stairsVisible = false;

public:

    // need args for enemy, item ptr
    Tile(Type type, int x, int y);
    std::string getType();

    std::string getChar();

    void setType(Type newType);

    void setEnemy(std::shared_ptr<Enemy> newEnemy);
    std::shared_ptr<Enemy> getEnemy();

    void setItem(std::shared_ptr<Item> newItem);

    std::shared_ptr<Item> getItem();

    void setStairsVisible();

};

#endif
