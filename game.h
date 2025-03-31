#ifndef GAME_H
#define GAME_H

#include "subject.h"
#include "floor.h"
#include "tile.h"
#include "playerChar.h"
#include "enemy.h"
#include "enemyFactory.h"
#include "item.h"
#include "itemFactory.h"

#include <sstream>
#include <utility>
#include <vector>
#include <memory>
#include <random>

class Game : public Subject {
    // a floors coords runs from (0, 0) to (24, 78)
    static const int MAXFLOORS = 5;
    vector<shared_ptr<Floor>> floors;
    shared_ptr<PlayerChar> player;

    default_random_engine rng; // randomizer
    int currentFloor;
    int BSFloor; // floor the barrier suit will spawn
    double goldScore;

    // so we can display both the player
    // and enemy action in a turn.
    // See Figure 3 in cc3k+ pdf.
    string playerCommandLine;
    string enemyCommandLine;
    int stairsX;
    int stairsY;

public:
    Game(shared_ptr<PlayerChar> player, default_random_engine rng, int BSFloor);

    // HELPER FUNCTION TO RANDOMIZE SPAWNS
    vector<int> getRandomSpawn(vector<vector<int>>& chamberBounds);

    void initFloor();

    int getCurrentFloor();

    shared_ptr<Floor> getFloor(int floorNum);

    shared_ptr<PlayerChar> getPlayer();

    double getGoldScore();

    void displayGame();

    void setPlayerCommandLine(string &command);

    string getPlayerCommandLine();

    void setEnemyCommandLine(string &command);

    string getEnemyCommandLine();

    // game logic

    void move(string dir);

    void attack(string dir);

    void useItem(string dir);

    void enemyMove(shared_ptr<Enemy> enemy);

    void enemyRound();
};


#endif
