#ifndef GAME_H
#define GAME_H

#include "subject.h"
#include "floor.h"
#include "tile.h"
#include "playerChar.h"
#include "enemy.h"
#include "enemyFactory.h"
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

    unsigned seed; // randomizer
    int currentFloor;
    int goldScore;

    string commandLine;

public:
    Game(shared_ptr<PlayerChar> player, unsigned seed) 
    : player{player}, seed{seed}, currentFloor{1}, goldScore{0}, commandLine{"Player character has spawned."} {
        
        for(int i = 0; i < MAXFLOORS; ++i) {
            floors.push_back(make_shared<Floor>());
        }
    }

    // HELPER FUNCTION TO RANDOMIZE SPAWNS
    vector<int> getRandomSpawn(vector<vector<int>>& chamberBounds, unsigned seed) {
        default_random_engine rng{seed};
        shuffle(chamberBounds.begin(), chamberBounds.end(), rng);
        vector<int> spawnRow = chamberBounds.at(0);

        vector<int> xCoords;
        for (int i = spawnRow.at(0); i <= spawnRow.at(2); ++i) {
            xCoords.push_back(i);
        }

        shuffle(xCoords.begin(), xCoords.end(), rng);
        vector<int> resultCoords;
        resultCoords.push_back(xCoords.at(0));
        resultCoords.push_back(spawnRow.at(1));

        return resultCoords;
    }

    void initFloor() {
        shared_ptr<Floor> curFloor = getFloor(currentFloor);

        // RANDOMIZING PLAYER/STAIRS SPAWN
        vector<Floor::Chamber> chambers = curFloor->getChambers();
        default_random_engine rng{seed};
        shuffle(chambers.begin(), chambers.end(), rng); // randomize chamber
        Floor::Chamber playerSpawn = chambers.at(0);
        Floor::Chamber stairsSpawn = chambers.at(1);

        // get random spawn for player
        vector<vector<int>> playerChamberBounds = curFloor->getChamberBounds(playerSpawn);
        vector<int> playerCoords = getRandomSpawn(playerChamberBounds, seed);
        int playerX = playerCoords.at(0);
        int playerY = playerCoords.at(1);

        // get random spawn for stairs
        vector<vector<int>> stairsChamberBounds = curFloor->getChamberBounds(stairsSpawn);
        vector<int> stairsCoords = getRandomSpawn(stairsChamberBounds, seed);
        int stairsX = stairsCoords.at(0);
        int stairsY = stairsCoords.at(1);

        // SET PLAYER SPAWN
        curFloor->getTile(playerX, playerY)->setType(Tile::PLAYER); 
        player->setPos(playerX, playerY);

        // SET STAIRS SPAWN
        curFloor->getTile(stairsX, stairsY)->setType(Tile::STAIRS);
        curFloor->getTile(stairsX, stairsY)->setStairsVisible(); // TEMP GET RID OF, MAKES STAIRS VISIBLE

        // SPAWN POTIONS

        // SPAWN GOLD

        // SPAWN ENEMIES

	    // testing an enemy spawn
	    int x = 27;
	    int y = 6;

        // no randomness yet, only generates werewolf
	    shared_ptr<Enemy> enemyTest = EnemyFactory::createEnemy();
	    curFloor->getTile(x, y)->setType(Tile::ENEMY); // sets enemyTest spawn
        curFloor->getTile(x, y)->setEnemy(enemyTest);
	    enemyTest->setPos(x, y);
	
    }

    int getCurrentFloor() {
        return currentFloor;
    }

    shared_ptr<Floor> getFloor(int floorNum) {
        return floors.at(floorNum - 1);
    }

    shared_ptr<PlayerChar> getPlayer() {
        return player;
    }

    int getGoldScore() {
        return goldScore;
    }

    void displayGame() {
        notifyObservers();
    }

    void setCommandLine(string &command) {
        commandLine = command;
    }

    string getCommandLine() {
        return commandLine;
    }

    // game logic

    void move(string dir) {
        int curX = player->getX();
        int curY = player->getY();
        int tempX = player->getX();
        int tempY = player->getY();
        string direction;

        if (dir == "no") { 
            tempY -= 1;
            direction = "North";
        } else if (dir == "so") {
            tempY += 1;
            direction = "South";
        } else if (dir == "ea") {
            tempX += 1;
            direction = "East";
        } else if (dir == "we") {
            tempX -= 1;
            direction = "West";
        } else if (dir == "ne") {
            tempX += 1;
            tempY -= 1;
            direction = "Northeast";
        } else if (dir == "nw") {
            tempX -= 1;
            tempY -= 1;
            direction = "Northwest";
        } else if (dir == "se") {
            tempX += 1;
            tempY += 1;
            direction = "Southeast";
        } else if (dir == "sw") {
            tempX -= 1;
            tempY += 1;
            direction = "Southwest";
        } 

        string actionResult;
        shared_ptr<Floor> curFloor = getFloor(currentFloor);
        
        // check nextTile validity
        shared_ptr<Tile> nextTile = curFloor->getTile(tempX, tempY);
        string nextTileType = nextTile->getType();

        // if empty
        if (nextTileType == "empty") {
            nextTile->setType(Tile::PLAYER);
            player->setPos(tempX, tempY);
            curFloor->getTile(curX, curY)->setType(Tile::EMPTY);
            
            actionResult = "PC moves " + direction;
        
        // if passage
        } else if (nextTileType == "passage") {
            nextTile->setType(Tile::PLAYER);
            player->setPos(tempX, tempY);
            curFloor->getTile(curX, curY)->setType(Tile::PASSAGE);
            
            actionResult = "PC crawls " + direction;

        // if door
        } else if (nextTileType == "door") {
            if (player->isInPassage()) {
                // find empty tile
                if (curFloor->getTile(tempX + 1, tempY)->getType() == "empty") {
                    tempX += 1;
                } else if (curFloor->getTile(tempX - 1, tempY)->getType() == "empty") {
                    tempX -= 1;
                } else if (curFloor->getTile(tempX, tempY + 1)->getType() == "empty") {
                    tempY += 1;
                } else {
                    tempY -= 1;
                }

                curFloor->getTile(curX, curY)->setType(Tile::PASSAGE);
                player->setInPassage(false);
                actionResult = "PC crawled out of the passage";

            } else {
                // find passage tile
                if (curFloor->getTile(tempX + 1, tempY)->getType() == "passage") {
                    tempX += 1;
                } else if (curFloor->getTile(tempX - 1, tempY)->getType() == "passage") {
                    tempX -= 1;
                } else if (curFloor->getTile(tempX, tempY + 1)->getType() == "passage") {
                    tempY += 1;
                } else {
                    tempY -= 1;
                }

                curFloor->getTile(curX, curY)->setType(Tile::EMPTY);
                player->setInPassage(true);
                actionResult = "PC entered a passage";
            }

            curFloor->getTile(tempX, tempY)->setType(Tile::PLAYER);
            player->setPos(tempX, tempY);
            
        } else {
            actionResult = "You are trying to move out of bounds, try again.";
        } // more else ifs depending on what the tile is

        setCommandLine(actionResult);
    }

    void enemyMove(shared_ptr<Enemy> enemy) {
	    if (!(enemy->getMoved())) {
	        int curX = enemy->getX();
            int curY = enemy->getY();

	        shared_ptr<Floor> curFloor = getFloor(currentFloor);
	        vector<pair<int, int>> validMoves;
	        bool attack = false;
	        string actionResult;

	        // get enemy's potential moves, stop if player is found
            // unless enemy is a merchant/dragon and is not hostile
	        for (int i = curX-1; i <= curX+1; i++) {
            	for (int j = curY-1; j <= curY+1; j++) {
	    	        if (i != curX || j != curY) {
		    	        if (curFloor->getTile(i, j)->getType() == "empty") {
			                validMoves.emplace_back(make_pair(i,j));
		   	            } else if (enemy->isHostile()) {
                            if (curFloor->getTile(i, j)->getType() == "player") {
			                    attack = true;
			                    break;
                            }
		    	        }
	    	        }
            	}
    	    }

	        if (attack) {
		        // for now they always hit, but
                // enemy attacks have 50% accuracy
                // let's say 0-49 is miss, 50-99 is hit
                int rand = 50;
                if (rand > 49) {
                    // The extra (100 + player DEF - 1) is there so it rounds up
                    int damage = ((100 + 100 + getPlayer()->getDEF() - 1)/(100 + getPlayer()->getDEF())) * enemy->getATK();
                    // if (BarrierSuit) {
                    // damage = ceil(damage / 2) 
                    // }
                    ostringstream oss;
                    oss << enemy->getSymbol() << " deals " << damage << " damage to PC.";
                    actionResult += oss.str();
                } else {
		            actionResult += enemy->getSymbol();
                    actionResult += " attacks PC but misses.";
                }
		        setCommandLine(actionResult);
	        } else {
	    	    // pick a direction and go in it
	    	    // would be generated between 0 and
	    	    // surroundings.size()
	    	    int rand = 0;
	    	    shared_ptr<Tile> nextTile = curFloor->getTile(validMoves[rand].first, validMoves[rand].second);
	    	    nextTile->setType(Tile::ENEMY);
		        nextTile->setEnemy(enemy);
            	enemy->setPos(validMoves[rand].first, validMoves[rand].second);
            	curFloor->getTile(curX, curY)->setType(Tile::EMPTY);
	        }

	        enemy->setMoved();
	    }
    }

    void enemyRound() {
	    shared_ptr<Floor> curFloor = getFloor(currentFloor);    
    	for (int i = 0; i < 79; i++) {
	        for (int j = 0; j < 25; j++) {
	            if (curFloor->getTile(i,j)->getType() == "enemy") {
		            enemyMove(curFloor->getTile(i,j)->getEnemy());
		        }    
	        }
	    }

	    for (int i = 0; i < 79; i++) {
            for (int j = 0; j < 25; j++) {
                if (curFloor->getTile(i,j)->getType() == "enemy") {	
                    curFloor->getTile(i,j)->getEnemy()->resetMoved();
                }
            }
        }
    }
};


#endif
