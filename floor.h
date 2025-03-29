#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"
#include <vector>
#include <memory>
#include <string>

class Floor {
    static const int HEIGHT = 25;
    static const int WIDTH = 79;
    string layout = "|-----------------------------------------------------------------------------||                                                                             || |--------------------------|        |-----------------------|               || |..........................|        |.......................|               || |..........................+########+.......................|-------|       || |..........................|   #    |...............................|--|    || |..........................|   #    |..................................|--| || |----------+---------------|   #    |----+----------------|...............| ||            #                 #############                |...............| ||            #                 #     |-----+------|         |...............| ||            #                 #     |............|         |...............| ||            ###################     |............|   ######+...............| ||            #                 #     |............|   #     |...............| ||            #                 #     |-----+------|   #     |--------+------| ||  |---------+-----------|     #           #          #              #        ||  |.....................|     #           #          #         |----+------| ||  |.....................|     ########################         |...........| ||  |.....................|     #           #                    |...........| ||  |.....................|     #    |------+--------------------|...........| ||  |.....................|     #    |.......................................| ||  |.....................+##########+.......................................| ||  |.....................|          |.......................................| ||  |---------------------|          |---------------------------------------| ||                                                                             ||-----------------------------------------------------------------------------|";

    vector<vector<shared_ptr<Tile>>> Tiles;


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

            Tiles.push_back(row);
        }
    }

    vector<vector<shared_ptr<Tile>>> getTiles() {
        return Tiles;
    }
};

#endif