#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"
#include <vector>
#include <memory>
#include <string>

class Floor {

public:
    enum Chamber {
        TOPLEFT, TOPRIGHT, MIDDLE, BOTTOMLEFT, BOTTOMRIGHT
    };

protected:
    static const int HEIGHT = 25;
    static const int WIDTH = 79;
    string layout = "|-----------------------------------------------------------------------------||                                                                             || |--------------------------|        |-----------------------|               || |..........................|        |.......................|               || |..........................+########+.......................|-------|       || |..........................|   #    |...............................|--|    || |..........................|   #    |..................................|--| || |----------+---------------|   #    |----+----------------|...............| ||            #                 #############                |...............| ||            #                 #     |-----+------|         |...............| ||            #                 #     |............|         |...............| ||            ###################     |............|   ######+...............| ||            #                 #     |............|   #     |...............| ||            #                 #     |-----+------|   #     |--------+------| ||  |---------+-----------|     #           #          #              #        ||  |.....................|     #           #          #         |----+------| ||  |.....................|     ########################         |...........| ||  |.....................|     #           #                    |...........| ||  |.....................|     #    |------+--------------------|...........| ||  |.....................|     #    |.......................................| ||  |.....................+##########+.......................................| ||  |.....................|          |.......................................| ||  |---------------------|          |---------------------------------------| ||                                                                             ||-----------------------------------------------------------------------------|";

    // CHAMBER INFO:
    vector<Chamber> chambers = {TOPLEFT, TOPRIGHT, MIDDLE, BOTTOMLEFT, BOTTOMRIGHT};

    // chamber coordinate bounds (by row): (top left tile is (0, 0))
    
    // chamber topleft (1): 
    // (3, 3) -> (28, 3)
    // (3, 4) -> (28, 4)
    // (3, 5) -> (28, 5)
    // (3, 6) -> (28, 6)
    vector<vector<int>> tlBounds = {
        {3, 3, 28}, {3, 4, 28}, {3, 5, 28}, {3, 6, 28}
    };

    // chamber topright:
    // (39, 3) -> (61, 3)
    // (39, 4) -> (61, 4)
    // (39, 5) -> (69, 5)
    // (39, 6) -> (72, 6)
    // (61, 7) -> (75, 7)
    // (61, 8) -> (75, 8)
    // (61, 9) -> (75, 9)
    // (61, 10) -> (75, 10)
    // (61, 11) -> (75, 11)
    // (61, 12) -> (75, 12)
    vector<vector<int>> trBounds = {
        {39, 3, 61}, {39, 4, 61}, {39, 5, 69}, {39, 6, 72},
        {61, 7, 75}, {61, 8, 75}, {61, 9, 75}, {61, 10, 75},
        {61, 11, 75}, {61, 12, 75}
    };

    // chamber middle:
    // (38, 10) -> (49, 10)
    // (38, 11) -> (49, 11)
    // (38, 12) -> (49, 12)
    vector<vector<int>> mBounds = {
        {38, 10, 49}, {38, 11, 49}, {38, 12, 49}
    };

    // chamber bottomleft:
    // (4, 15) -> (24, 15)
    // (4, 16) -> (24, 16)
    // (4, 17) -> (24, 17)
    // (4, 18) -> (24, 18)
    // (4, 19) -> (24, 19)
    // (4, 20) -> (24, 20)
    // (4, 21) -> (24, 21)
    vector<vector<int>> blBounds = {
        {4, 15, 24}, {4, 16, 24}, {4, 17, 24}, {4, 18, 24},
        {4, 19, 24}, {4, 20, 24}, {4, 21, 24}
    };

    // chamber bottomright:
    // (65, 16) -> (75, 16)
    // (65, 17) -> (75, 17)
    // (65, 18) -> (75, 18)
    // (37, 19) -> (75, 19)
    // (37, 20) -> (75, 20)
    // (37, 21) -> (75, 21)
    vector<vector<int>> brBounds = {
        {65, 16, 75}, {65, 17, 75}, {65, 18, 75}, {37, 19, 75},
        {37, 20, 75}, {37, 21, 75}
    };

    vector<vector<shared_ptr<Tile>>> tiles;


public:

    Floor() {

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

    vector<vector<shared_ptr<Tile>>> getTiles() {
        return tiles;
    }

    shared_ptr<Tile> getTile(int x, int y) {
        return tiles.at(y).at(x);
    }

    vector<Chamber> getChambers() {
        return chambers;
    }

    vector<vector<int>> getChamberBounds(Chamber chamber) {
        switch (chamber) {
            case TOPLEFT: return tlBounds; break;
            case TOPRIGHT: return trBounds; break;
            case MIDDLE: return mBounds; break;
            case BOTTOMLEFT: return blBounds; break;
            case BOTTOMRIGHT: return brBounds; break;
            default: return mBounds; break;
        }
    }
};

#endif