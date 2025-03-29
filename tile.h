#ifndef TILE_H
#define TILE_H

#include <string>
#include "enemy.h"

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
    shared_ptr<Enemy> enemy;
    // shared_ptr<Item> Item;

    int x, y;
    bool stairsVisible = false;

public:

    // need args for enemy, item ptr
    Tile(Type type, int x, int y) : type{type}, x{x}, y{y} {};

    string getType() {
        switch (type) {
            case WS: return "ws"; break;
            case VWALL: return "vWall"; break;
            case HWALL: return "hWall"; break;
            case PASSAGE: return "passage"; break;
            case DOOR: return "door"; break;
            case STAIRS: return "stairs"; break;
            case EMPTY: return "empty"; break;
            case PLAYER: return "player"; break;
            case ENEMY: return "enemy"; break;
            case ITEM: return "item"; break;
            default: return "?"; break;
        }
    }

    char getChar() {
        switch (type) {
            case WS: return ' '; break;
            case VWALL: return '|'; break;
            case HWALL: return '-'; break;
            case PASSAGE: return '#'; break;
            case DOOR: return '+'; break;
            case STAIRS: return (stairsVisible) ? '/' : '.'; break;
            case EMPTY: return '.'; break;
            case PLAYER: return '@'; break;
            case ENEMY: return enemy->getSymbol(); break;
            // case ITEM: return Item->getSymbol; break;
            default: return '?'; break;
        }
    }

    void setType(Type newType) {
        type = newType;
    }

    void setEnemy(shared_ptr<Enemy> newEnemy) {
	    enemy = newEnemy;
    }

    shared_ptr<Enemy> getEnemy() {
        return enemy;
    }

    void setStairsVisible() {
        stairsVisible = true;
    }

};

#endif
