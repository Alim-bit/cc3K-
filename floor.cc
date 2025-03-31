#include "floor.h"
using namespace std;

Floor::Floor() {

    int index = 0;
    for (int r = 0; r < HEIGHT; ++r) {
        vector<shared_ptr<Tile>> row;
        for (int c = 0; c < WIDTH; ++c) {
            char chr = layout[index++];
            Tile::Type type;

            switch (chr) {
                case ' ': type = Tile::WS; break;
                case '|': type = Tile::VWALL; break;
                case '-': type = Tile::HWALL; break;
                case '#': type = Tile::PASSAGE; break;
                case '+': type = Tile::DOOR; break;
                case '.': type = Tile::EMPTY; break;
                default: type = Tile::WS; 
            }
        
            row.push_back(make_shared<Tile>(type, c, r));
        }

        tiles.push_back(row);
    }
}

vector<vector<shared_ptr<Tile>>> Floor::getTiles() {
    return tiles;
}

shared_ptr<Tile> Floor::getTile(int x, int y) {
    return tiles.at(y).at(x);
}

vector<Floor::Chamber> Floor::getChambers() {
    return chambers;
}

vector<vector<int>> Floor::getChamberBounds(Chamber &chamber) {
    switch (chamber) {
        case TOPLEFT: return tlBounds; break;
        case TOPRIGHT: return trBounds; break;
        case MIDDLE: return mBounds; break;
        case BOTTOMLEFT: return blBounds; break;
        case BOTTOMRIGHT: return brBounds; break;
        default: return mBounds; break;
    }
}
