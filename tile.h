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
    Tile(Type type, int x, int y) : type{type}, x{x}, y{y} {};

    std::string getType() {
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

    std::string getChar() {
        const std::string RESET = "\033[0m";
        const std::string BLUE = "\033[34m";   // for player/stairs
        const std::string RED = "\033[31m";    // for enemies
        const std::string YELLOW = "\033[33m"; // for treasure
        const std::string GREEN = "\033[32m";  // for potions

        switch (type) {
            case WS: return " "; break;
            case VWALL: return "|"; break;
            case HWALL: return "-"; break;
            case PASSAGE: return "#"; break;
            case DOOR: return "+"; break;
            case STAIRS: return (stairsVisible) ? BLUE + "/" + RESET : "."; break;
            case EMPTY: return "."; break;
            case PLAYER: return BLUE + "@" + RESET; break;
            case ENEMY: return RED + std::string(1, enemy->getSymbol()) + RESET; break;
            case ITEM: 
                if (item->getName() == "NG" || item->getName() == "SH" ||
                    item->getName() == "MH" || item->getName() == "DH" ||
                    item->getName() == "C" || item->getName() == "BS") {
                    return YELLOW + std::string(1, item->getSymbol()) + RESET; 
                } else {
                    return GREEN + std::string(1, item->getSymbol()) + RESET; 
                }
            default: return "?"; break;
        }
    }

    void setType(Type newType) {
        type = newType;
    }

    void setEnemy(std::shared_ptr<Enemy> newEnemy) {
	    enemy = newEnemy;
    }

    std::shared_ptr<Enemy> getEnemy() {
        return enemy;
    }

    void setItem(std::shared_ptr<Item> newItem) {
	    item = newItem;
    }

    std::shared_ptr<Item> getItem() {
        return item;
    }

    void setStairsVisible() {
        stairsVisible = true;
    }

};

#endif
