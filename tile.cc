#include "tile.h"
using namespace std;

Tile::Tile(Type type, int x, int y) : type{type}, enemy{nullptr}, item{nullptr}, x{x}, y{y} {};

string Tile::getType() {
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

string Tile::getChar() {
    const string RESET = "\033[0m";
    const string BLUE = "\033[34m";   // for player/stairs
    const string RED = "\033[31m";    // for enemies
    const string YELLOW = "\033[33m"; // for treasure
    const string GREEN = "\033[32m";  // for potions

    switch (type) {
        case WS: return " "; break;
        case VWALL: return "|"; break;
        case HWALL: return "-"; break;
        case PASSAGE: return "#"; break;
        case DOOR: return "+"; break;
        case STAIRS: return (stairsVisible) ? BLUE + "/" + RESET : "."; break;
        case EMPTY: return "."; break;
        case PLAYER: return BLUE + "@" + RESET; break;
        case ENEMY: return RED + string(1, enemy->getSymbol()) + RESET; break;
        case ITEM: 
            if (item->getName() == "NG" || item->getName() == "SH" ||
                item->getName() == "MH" || item->getName() == "DH" ||
                item->getName() == "C" || item->getName() == "BS") {
                return YELLOW + string(1, item->getSymbol()) + RESET; 
            } else {
                return GREEN + string(1, item->getSymbol()) + RESET; 
            }
        default: return "?"; break;
    }
}

void Tile::setType(Type newType) {
    type = newType;
}

void Tile::setEnemy(shared_ptr<Enemy> newEnemy) {
	enemy = newEnemy;
}

shared_ptr<Enemy> Tile::getEnemy() {
    return enemy;
}

void Tile::setItem(shared_ptr<Item> newItem) {
	item = newItem;
}

shared_ptr<Item> Tile::getItem() {
    return item;
}

void Tile::setStairsVisible() {
    stairsVisible = true;
}
