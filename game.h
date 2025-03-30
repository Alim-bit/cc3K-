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

    int currentFloor;
    int goldScore;
    default_random_engine rng; // randomizer

    string commandLine;

public:
    Game(shared_ptr<PlayerChar> player, default_random_engine rng) 
    : player{player}, rng{rng}, currentFloor{1}, goldScore{0}, commandLine{"Player character has spawned."} {

        for(int i = 0; i < MAXFLOORS; ++i) {
            floors.push_back(make_shared<Floor>());
        }
    }

    // HELPER FUNCTION TO RANDOMIZE SPAWNS
    vector<int> getRandomSpawn(vector<vector<int>>& chamberBounds) {
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
        shuffle(chambers.begin(), chambers.end(), rng); // randomize chamber
        Floor::Chamber playerSpawn = chambers.at(0);
        Floor::Chamber stairsSpawn = chambers.at(1);

        // get random spawn for player
        vector<vector<int>> playerChamberBounds = curFloor->getChamberBounds(playerSpawn);
        vector<int> playerCoords = getRandomSpawn(playerChamberBounds);
        int playerX = playerCoords.at(0);
        int playerY = playerCoords.at(1);

        // get random spawn for stairs
        vector<vector<int>> stairsChamberBounds = curFloor->getChamberBounds(stairsSpawn);
        vector<int> stairsCoords = getRandomSpawn(stairsChamberBounds);
        int stairsX = stairsCoords.at(0);
        int stairsY = stairsCoords.at(1);

        // SET PLAYER SPAWN
        curFloor->getTile(playerX, playerY)->setType(Tile::PLAYER); 
        player->setPos(playerX, playerY);

        // SET STAIRS SPAWN
        curFloor->getTile(stairsX, stairsY)->setType(Tile::STAIRS);
        curFloor->getTile(stairsX, stairsY)->setStairsVisible(); // TEMP GET RID OF, MAKES STAIRS VISIBLE

        // SPAWN POTIONS
        int numPotions = 10;
        vector<string> potionTypes = {"RH", "BA", "BD", "PH", "WA", "WD"};
        for (int i = 0; i < numPotions; ++i) {
            // Create a vector of chamber indices and shuffle it
            vector<int> chamberIndices(chambers.size());
            for (size_t j = 0; j < chambers.size(); ++j) {
                chamberIndices[j] = j;
            }
            shuffle(chamberIndices.begin(), chamberIndices.end(), rng);
            int chosenIndex = chamberIndices[0];
            Floor::Chamber chosenChamber = chambers.at(chosenIndex);
            
            vector<vector<int>> bounds = curFloor->getChamberBounds(chosenChamber);
            // Sorry I changed this, why was it seed + i + 10 ?
            vector<int> coords = getRandomSpawn(bounds);
            int x = coords.at(0);
            int y = coords.at(1);
            shared_ptr<Tile> tile = curFloor->getTile(x, y);
            if (tile->getType() == "empty") {
                // Shuffle a copy of the potion types and pick the first one
                vector<string> tempPotionTypes = potionTypes;
                shuffle(tempPotionTypes.begin(), tempPotionTypes.end(), rng);
                string pType = tempPotionTypes[0];
                // Create potion using the ItemFactory (returns a unique_ptr<Item>)
                unique_ptr<Item> potion = ItemFactory::create(pType, tile->getCell(), curFloor.get());
                tile->setType("potion");
                curFloor->addItem(move(potion));
            }
        }
        


        // SPAWN GOLD
        int numGoldPiles = 10;
        // Build a gold pool based on probabilities: normal (5/8), dragon hoard (1/8), small hoard (2/8)
        vector<string> goldPool;
        for (int i = 0; i < 5; ++i) {
            goldPool.push_back("NormalGold");
        }
        for (int i = 0; i < 1; ++i) {
            goldPool.push_back("DragonHoardGold");
        }
        for (int i = 0; i < 2; ++i) {
            goldPool.push_back("SmallHoardGold");
        }
        for (int i = 0; i < numGoldPiles; ++i) {
            vector<int> chamberIndices(chambers.size());
            for (size_t j = 0; j < chambers.size(); ++j) {
                chamberIndices[j] = j;
            }
            shuffle(chamberIndices.begin(), chamberIndices.end(), rng);
            int chosenIndex = chamberIndices[0];
            Floor::Chamber chosenChamber = chambers.at(chosenIndex);
            
            vector<vector<int>> bounds = curFloor->getChamberBounds(chosenChamber);
            vector<int> coords = getRandomSpawn(bounds);
            int x = coords.at(0);
            int y = coords.at(1);
            shared_ptr<Tile> tile = curFloor->getTile(x, y);
        if (tile->getType() == "empty") {
            // Shuffle a copy of the gold pool and choose the first type
            vector<string> tempGoldPool = goldPool;
            shuffle(tempGoldPool.begin(), tempGoldPool.end(), rng);
                string gType = tempGoldPool[0];
                unique_ptr<Item> gold = ItemFactory::create(gType, tile->getCell(), curFloor.get());
                tile->setType("gold");
                curFloor->addItem(move(gold));
            }
        }

        // SPAWN ENEMIES
        // With items, will be i < 20 - number of dragon hoards, since
        // dragons are spawned separately (and there are 20 enemies per floor)
        uniform_int_distribution<int> enemyProbability(1,18);
         for (int i = 0; i < 20; i++) {
            shared_ptr<Enemy> spawnedEnemy = EnemyFactory::createEnemy(enemyProbability(rng));

            shuffle(chambers.begin(), chambers.end(), rng);
            Floor::Chamber enemySpawn = chambers.at(0);
            vector<vector<int>> enemyChamberBounds = curFloor->getChamberBounds(enemySpawn);

            // generates coords for the enemy until it finds one that isn't on top of something else
            vector<int> enemyCoords;
            while (true) {
                vector<int> tempCoords = getRandomSpawn(enemyChamberBounds, rng);
                if (curFloor->getTile(tempCoords.at(0), tempCoords.at(1))->getType() == "empty") {
                    enemyCoords = tempCoords;
                    break;
                }
            }
            int enemyX = enemyCoords.at(0);
            int enemyY = enemyCoords.at(1);

            curFloor->getTile(enemyX, enemyY)->setType(Tile::ENEMY);
            spawnedEnemy->setPos(enemyX, enemyY);
            curFloor->getTile(enemyX, enemyY)->setEnemy(spawnedEnemy);
        }
	
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
            
        } else if (nextTileType == "stairs") {
            currentFloor += 1;
            initFloor();

            actionResult = "You have made it to floor" + to_string(currentFloor);

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
                    getPlayer()->setHP(getPlayer()->getHP() - damage);
                    ostringstream oss;
                    oss << enemy->getSymbol() << " deals " << damage << " damage to PC.";
                    actionResult += oss.str();
                } else {
		            actionResult += enemy->getSymbol();
                    actionResult += " attacks PC but misses.";
                }
		        setCommandLine(actionResult);
	        } else {
	    	    // randomly selects a move out of validMoves
		        if (validMoves.size() != 0) {
			        shuffle(validMoves.begin(), validMoves.end(), rng);
			        pair<int, int> newCoords = validMoves.at(0);
			        shared_ptr<Tile> nextTile = curFloor->getTile(newCoords.first, newCoords.second);
                   
			        nextTile->setType(Tile::ENEMY);
			        nextTile->setEnemy(enemy);
			        enemy->setPos(newCoords.first, newCoords.second);
			        curFloor->getTile(curX, curY)->setType(Tile::EMPTY);
                }
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
