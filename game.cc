#include "game.h"

using namespace std;

Game::Game(shared_ptr<PlayerChar> player, default_random_engine rng) 
: player{player}, rng{rng}, currentFloor{1}, goldScore{0}, playerCommandLine{"Player character has spawned."}, enemyCommandLine{""} {

    for(int i = 0; i < MAXFLOORS; ++i) {
        floors.push_back(make_shared<Floor>());
    }
}

// HELPER FUNCTION TO RANDOMIZE SPAWNS
vector<int> Game::getRandomSpawn(vector<vector<int>>& chamberBounds) {
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

void Game::initFloor() {
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
    stairsX = stairsCoords.at(0);
    stairsY = stairsCoords.at(1);

    // SET PLAYER SPAWN
    curFloor->getTile(playerX, playerY)->setType(Tile::PLAYER); 
    player->setPos(playerX, playerY);

    // SET POTIONS
    player->resetTempPotions();

    // SET STAIRS SPAWN
    curFloor->getTile(stairsX, stairsY)->setType(Tile::STAIRS);
    //curFloor->getTile(stairsX, stairsY)->setStairsVisible(); // TEMP GET RID OF, MAKES STAIRS VISIBLE

    // SPAWN POTIONS
    int numPotions = 10;
    uniform_int_distribution<int> potionProbability(1,6);
    for (int i = 0; i < numPotions; ++i) {
        int randPotion = potionProbability(rng);
        shared_ptr<Item> spawnedPotion;
        if (randPotion == 1) {
            spawnedPotion = ItemFactory::createItem("RH");
        } else if (randPotion == 2) {
            spawnedPotion = ItemFactory::createItem("BA");
        } else if (randPotion == 3) {
            spawnedPotion = ItemFactory::createItem("BD");
        } else if (randPotion == 4) {
            spawnedPotion = ItemFactory::createItem("PH");
        } else if (randPotion == 5) {
            spawnedPotion = ItemFactory::createItem("WA");
        } else {
            spawnedPotion = ItemFactory::createItem("WD");
        }
            
        shuffle(chambers.begin(), chambers.end(), rng);
        Floor::Chamber potionSpawn = chambers.at(0);
        vector<vector<int>> potionChamberBounds = curFloor->getChamberBounds(potionSpawn);

        // generates coords for the potion until it finds one that isn't on top of something else
        vector<int> potionCoords;
        while (true) {
            vector<int> tempCoords = getRandomSpawn(potionChamberBounds);
            if (curFloor->getTile(tempCoords.at(0), tempCoords.at(1))->getType() == "empty") {
                potionCoords = tempCoords;
                break;
            }
        }
        int potionX = potionCoords.at(0);
        int potionY = potionCoords.at(1);

        curFloor->getTile(potionX, potionY)->setType(Tile::ITEM);
        spawnedPotion->setPos(potionX, potionY);
        curFloor->getTile(potionX, potionY)->setItem(spawnedPotion);

    }


    // SPAWN GOLD
    int numGoldPiles = 10;
    //int numDragonHoards = 0
    uniform_int_distribution<int> goldProbability(1,8);
    // probabilities: normal (5/8), dragon hoard (1/8), small hoard (2/8)
    for (int i = 0; i < numGoldPiles; i++) {
        int randGold = goldProbability(rng);
        shared_ptr<Item> spawnedGold;
        if (randGold <= 5) {
            spawnedGold = ItemFactory::createItem("NG");
        } else if (randGold <= 7) {
            spawnedGold = ItemFactory::createItem("SH");
        } else {
            spawnedGold = ItemFactory::createItem("DH");
                // numDragonHoards++;
        }
            
        shuffle(chambers.begin(), chambers.end(), rng);
        Floor::Chamber goldSpawn = chambers.at(0);
        vector<vector<int>> goldChamberBounds = curFloor->getChamberBounds(goldSpawn);

        // generates coords for the gold until it finds one that isn't on top of something else
        vector<int> goldCoords;
        while (true) {
            vector<int> tempCoords = getRandomSpawn(goldChamberBounds);
            if (curFloor->getTile(tempCoords.at(0), tempCoords.at(1))->getType() == "empty") {
                goldCoords = tempCoords;
                break;
            }
        }
        int goldX = goldCoords.at(0);
        int goldY = goldCoords.at(1);

        curFloor->getTile(goldX, goldY)->setType(Tile::ITEM);
        spawnedGold->setPos(goldX, goldY);
        curFloor->getTile(goldX, goldY)->setItem(spawnedGold);

        if (spawnedGold->getName() == "DH") {
            // Spawns dragon and finds position for it in one of 8 tiles
            // surrounding dragon hoard. Makes dragon and hoard part
            // of protectedItem pair.
            shared_ptr<Enemy> dragon = EnemyFactory::createEnemy("Dragon");
            vector<pair<int, int>> validTiles;
            for (int i = goldX-1; i <= goldX+1; i++) {
                for (int j = goldY-1; j <= goldY+1; j++) {
                    if (i != goldX || j != goldY) {
                        if (curFloor->getTile(i, j)->getType() == "empty") {
                            validTiles.emplace_back(make_pair(i,j));
                        }
                    }
                }
            }
            shuffle(validTiles.begin(), validTiles.end(), rng);
            pair<int, int> newCoords = validTiles.at(0);
            shared_ptr<Tile> newTile = curFloor->getTile(newCoords.first, newCoords.second);
            newTile->setType(Tile::ENEMY);
            newTile->setEnemy(dragon);
            dragon->setPos(newCoords.first, newCoords.second);
            
            // giving access to each others' positions
            spawnedGold->setProtected(true);
            spawnedGold->setEnemyPos(newCoords.first, newCoords.second);
            dragon->setItemPos(goldX, goldY);
        }
    }

    // SPAWN ENEMIES
    // With items, will be i < 20 - number of dragon hoards, since
    // dragons are spawned separately (and there are 20 enemies per floor)
	int numEnemies = 20; //- numDragonHoards;
    uniform_int_distribution<int> enemyProbability(1,18);
    for (int i = 0; i < numEnemies; i++) {
        int randEnemy = enemyProbability(rng);
        shared_ptr<Enemy> spawnedEnemy; 
        if (randEnemy <= 4) {
            spawnedEnemy = EnemyFactory::createEnemy("Werewolf");
        } else if (randEnemy <= 7) {
            spawnedEnemy = EnemyFactory::createEnemy("Vampire");
        } else if (randEnemy <= 12) {
            spawnedEnemy = EnemyFactory::createEnemy("Goblin");
        } else if (randEnemy <= 14) {
            spawnedEnemy = EnemyFactory::createEnemy("Troll");
        } else if (randEnemy <= 16) {
            spawnedEnemy = EnemyFactory::createEnemy("Phoenix");
        } else {
            spawnedEnemy = EnemyFactory::createEnemy("Merchant");
        }

        shuffle(chambers.begin(), chambers.end(), rng);
        Floor::Chamber enemySpawn = chambers.at(0);
        vector<vector<int>> enemyChamberBounds = curFloor->getChamberBounds(enemySpawn);

        // generates coords for the enemy until it finds one that isn't on top of something else
        vector<int> enemyCoords;
        while (true) {
            vector<int> tempCoords = getRandomSpawn(enemyChamberBounds);
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

         if (i == 0) {
            // if this is the first enemy generated,
            // have it drop compass on death. Equivalent
            // to 1/20 chance for enemy to have it.
            spawnedEnemy->setHolding();
        }
    }
}

int Game::getCurrentFloor() {
    return currentFloor;
}

shared_ptr<Floor> Game::getFloor(int floorNum) {
    return floors.at(floorNum - 1);
}

shared_ptr<PlayerChar> Game::getPlayer() {
    return player;
}

double Game::getGoldScore() {
    return goldScore;
}

void Game::displayGame() {
    notifyObservers();
}

void Game::setPlayerCommandLine(string &command) {
    playerCommandLine = command;
}

string Game::getPlayerCommandLine() {
    return playerCommandLine;
}

void Game::setEnemyCommandLine(string &command) {
    enemyCommandLine = command;
}

string Game::getEnemyCommandLine() {
    return enemyCommandLine;
}


// game logic

void Game::move(string dir) {
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
            
        actionResult = "PC moves " + direction + ".";

        // look for potion
        for (int i = tempX-1; i <= tempX+1; i++) {
            for (int j = tempY-1; j <= tempY+1; j++) {
		    	if (curFloor->getTile(i, j)->getType() == "item") {
			        auto item = curFloor->getTile(i, j)->getItem();
                    if (item->getName() == "RH" || item->getName() == "BA" ||
                        item->getName() == "BD" || item->getName() == "PH" ||
                        item->getName() == "WA" || item->getName() == "WD") {
                        if (item->isKnown()) {
                            actionResult = "PC sees a " + item->getName() + " potion.";
                        } else {
                            actionResult = "PC sees an unknown potion.";
                        }
                    }
		   	    } 
	    	}
        }
    
    // if passage
    } else if (nextTileType == "passage") {
        nextTile->setType(Tile::PLAYER);
        player->setPos(tempX, tempY);
        curFloor->getTile(curX, curY)->setType(Tile::PASSAGE);
            
        actionResult = "PC crawls " + direction + ".";

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
            actionResult = "PC crawled out of the passage.";

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
            actionResult = "PC entered a passage.";
        }

        curFloor->getTile(tempX, tempY)->setType(Tile::PLAYER);
        player->setPos(tempX, tempY);
            
  
    } else if (nextTileType == "item") {
        // Get the item from the tile
        auto item = nextTile->getItem();
        if (item) {
            if (item->getName() == "C" || item->getName() == "NG" || 
                item->getName() == "SH" || item->getName() == "MH") {
                // Uses item, then walks on to spot where item was
                if (item->getName() == "C") {
                    actionResult = "PC picks up the Compass; the stairs are now visible.";
                } else {
                    if (player->getRace() == "Orc") {
                        actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was halved as an orc.";
                    } else if (player->getRace() == "Dwarf") {
                        actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was doubled as an dwarf.";
                    } else {
                        actionResult = "PC picks up gold (" + to_string(item->getValue()) + ").";
                    }
                }
                useItem(dir);

                nextTile->setType(Tile::PLAYER);
                player->setPos(tempX, tempY);
                curFloor->getTile(curX, curY)->setType(Tile::EMPTY);

            } else if (item->getName() == "DH" || item->getName() == "BS") {
                // check if protector is gone before letting player take
                // the item.
                shared_ptr<Tile> protectorTile = curFloor->getTile(item->getEnemyX(), item->getEnemyY());
                // Since all protectors are dragons and dragons are stationary, just check
                // if a dragon is in that position.
                if (!(protectorTile->getType() == "enemy" && protectorTile->getEnemy()->getName() == "Dragon")) {
                    item->setProtected(false);
                }

                if (!(item->isProtected())) {
                    useItem(dir);
                    if (item->getName() == "DH") {
                        if (player->getRace() == "Orc") {
                            actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was halved as an orc.";
                        } else if (player->getRace() == "Dwarf") {
                            actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was doubled as an dwarf.";
                        } else {
                            actionResult = "PC picks up gold (" + to_string(item->getValue()) + ").";
                        }
                    } else {
                        actionResult = "PC picks up " + item->getName() + "! Damage taken is halved permanently.";
                    }
                } else {
                    actionResult = "Defeat the dragon to collect the item!";
                }
            } else {
                actionResult = "You can't walk on that.";
            }
        }
    } else if (nextTileType == "stairs") {
        currentFloor += 1;

        if (currentFloor <= 5) { // as long as we aren't at the 5th floor yet, since otherwise we beat the game moving to the 6th
            initFloor();
            actionResult = "You have made it to floor " + to_string(currentFloor) + ".";
        }

    } else {
        actionResult = "You are trying to move out of bounds, try again.";
    } // more else ifs depending on what the tile is

    setPlayerCommandLine(actionResult);
}

void Game::attack(string dir) {
    int tempX = player->getX();
    int tempY = player->getY();

    if (dir == "no") { 
        tempY -= 1;
    } else if (dir == "so") {
        tempY += 1;
    } else if (dir == "ea") {
        tempX += 1;
    } else if (dir == "we") {
        tempX -= 1;
    } else if (dir == "ne") {
        tempX += 1;
        tempY -= 1;
    } else if (dir == "nw") {
        tempX -= 1;
        tempY -= 1;
    } else if (dir == "se") {
        tempX += 1;
        tempY += 1;
    } else if (dir == "sw") {
        tempX -= 1;
        tempY += 1;
    }

    string actionResult;
    shared_ptr<Floor> curFloor = getFloor(currentFloor);
        
    // check attackTile for enemy
    shared_ptr<Tile> attackTile = curFloor->getTile(tempX, tempY);
    string attackTileType = attackTile->getType();

    // if enemy
    if (attackTileType == "enemy") {
        shared_ptr<Enemy> enemy = attackTile->getEnemy();
        int damage = ((100 + 100 + enemy->getDEF() - 1)/(100 + enemy->getDEF())) * (player->getATK() + player->getTempATK());
            
        enemy->setHP(enemy->getHP() - damage);
        ostringstream oss;

        // if enemy is defeated
        if (enemy->getHP() <= 0) {
            // this should delete the enemey when attack function ends
            // since all the shared_ptrs are gone.
            attackTile->setType(Tile::EMPTY);
            attackTile->setEnemy(nullptr);

            // Enemy is holding compass
            if (enemy->getHolding()) {
                shared_ptr<Item> compass = ItemFactory::createItem("C");
                attackTile->setType(Tile::ITEM);
                attackTile->setItem(compass);
                compass->setPos(tempX, tempY);
            }

            // Enemy is a merchant, drops merchant hoard
            if (enemy->getName() == "Merchant") {
                shared_ptr<Item> newMerchHoard = ItemFactory::createItem("MH");
                attackTile->setType(Tile::ITEM);
                attackTile->setItem(newMerchHoard);
                newMerchHoard->setPos(tempX, tempY);
            }

            // Enemy is not merchant/dragon
            if (!(enemy->getName() == "Merchant" || enemy->getName() == "Dragon")) {

                if (player->getRace() == "Orc") {
                    goldScore += 0.5;
                } else if (player->getRace() == "Dwarf") {
                    goldScore += 2;
                } else {
                    goldScore += 1;
                }
            }

            oss << "PC defeated " << enemy->getSymbol() << ".";
            actionResult += oss.str();

        // if enemy is not defeated
        } else {

            oss << "PC deals " << damage << " damage to " << enemy->getSymbol() << " (" << enemy->getHP() << " HP).";
            actionResult += oss.str();
        }
        // makes all merchants permanently hostile, and the attacked dragon
        // hostile for the next turn
        if (enemy->getName() == "Merchant" || enemy->getName() == "Dragon") {
            enemy->makeHostile();
        }

    // if empty    
    } else if (attackTileType == "empty") {
            
        actionResult = "You attack the empty air.";
        
    // if anything else    
    } else {
        actionResult = "You can't attack that.";
    }

    setPlayerCommandLine(actionResult);

}

void Game::useItem(string dir) {
    int tempX = player->getX();
    int tempY = player->getY();

    if (dir == "no") { 
        tempY -= 1;
    } else if (dir == "so") {
        tempY += 1;
    } else if (dir == "ea") {
        tempX += 1;
    } else if (dir == "we") {
        tempX -= 1;
    } else if (dir == "ne") {
        tempX += 1;
        tempY -= 1;
    } else if (dir == "nw") {
        tempX -= 1;
        tempY -= 1;
    } else if (dir == "se") {
        tempX += 1;
        tempY += 1;
    } else if (dir == "sw") {
        tempX -= 1;
        tempY += 1;
    }

    string actionResult;
    shared_ptr<Floor> curFloor = getFloor(currentFloor);

    // check itemTile for item
    shared_ptr<Tile> itemTile = curFloor->getTile(tempX, tempY);
    string itemTileType = itemTile->getType();

    if (itemTileType == "item") {
        // Get the item from the tile
        auto item = itemTile->getItem();
        if (item) {
            if (item->getName() == "C") {
                // When picking up the Compass, reveal the stairs.
                curFloor->getTile(stairsX, stairsY)->setStairsVisible();
                actionResult = "PC picks up the Compass; the stairs are now visible.";
            }
            else if (item->getName() == "NG" || item->getName() == "SH" ||
                    item->getName() == "MH" || item->getName() == "DH") {
                // For gold items, update the gold score.
                // goldScore += player->collectGold(item->getValue());
                if (player->getRace() == "Orc") {
                    goldScore += static_cast<double>(item->getValue()) / 2;
                    actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was halved as an orc.";
                } else if (player->getRace() == "Dwarf") {
                    goldScore += item->getValue() * 2;
                    actionResult = "PC picks up gold (" + to_string(item->getValue()) + ") which was doubled as an elf.";
                } else {
                    goldScore += item->getValue();
                    actionResult = "PC picks up gold (" + to_string(item->getValue()) + ").";
                }

            }
            else if (item->getName() == "BS") {
                actionResult = "PC picks up " + item->getName() + "! Damage taken is halved permanently.";
                // barrierSuit = true
            } else {
                player->drinkPotion(item->getName());
                actionResult = "PC drank a " + item->getName() + " potion.";
			    item->makeKnown();
            }
            // Remove the item from the tile
            itemTile->setType(Tile::EMPTY);
            itemTile->setItem(nullptr);
        }
    } else {
        actionResult = "You can't use that!";
    }

    setPlayerCommandLine(actionResult);
}

void Game::enemyMove(shared_ptr<Enemy> enemy) {
	if (!(enemy->getMoved())) {
	    int curX = enemy->getX();
        int curY = enemy->getY();

	    shared_ptr<Floor> curFloor = getFloor(currentFloor);
	    vector<pair<int, int>> validMoves;
	    bool attack = false;
	    string actionResult;

        // If enemy->getName() == "Dragon"
        // check its associated protectedItem
        // to see if the player is around it.
        // If so, become hostile.
        if (enemy->getName() == "Dragon") {
            int itemX = enemy->getItemX();
            int itemY = enemy->getItemY();
            for (int i = itemX-1; i <= itemX+1; i++) {
                for (int j = itemY-1; j <= itemY+1; j++) {
                    if (i != itemX || j != itemY) {
                        if (curFloor->getTile(i, j)->getType() == "player") {
                            enemy->makeHostile();
                            break;
                           } 
                    }
                }
            }
    
        }

	    // get enemy's potential moves, stop if player is found
        // unless enemy is a merchant/dragon and is not hostile
	    for (int i = curX-1; i <= curX+1; i++) {
            for (int j = curY-1; j <= curY+1; j++) {
	    	    if (i != curX || j != curY) {
		    	    if (curFloor->getTile(i, j)->getType() == "empty") {
			            validMoves.emplace_back(make_pair(i,j));
                        
                    // enemies only look for player if they are hostile
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
            // enemy attacks have 50% accuracy
            // 0-49 is miss, 50-99 is hit
            uniform_int_distribution<int> hitChance(0,99);
            int rand = hitChance(rng);
            if (rand > 49) {
                // The extra (100 + player DEF - 1) is there so it rounds up
                int damage = ((100 + 100 + (player->getDEF() + player->getTempDEF()) - 1)/(100 + (player->getDEF() + player->getTempDEF()))) * enemy->getATK();

                // if (BarrierSuit) {
                // damage = ceil(damage / 2) 
                // }

                player->setHP(player->getHP() - damage);
                ostringstream oss;
                oss << " " << enemy->getSymbol() << " deals " << damage << " damage to PC.";
                actionResult += oss.str();

            } else {
                actionResult += " ";
		        actionResult += enemy->getSymbol();
                actionResult += " attacks PC but misses.";

            }

		    setEnemyCommandLine(actionResult);

	    } else {
	    	// randomly selects a move out of validMoves
            // unless enemy is Dragon, which doesn't move
            if (!(enemy->getName() == "Dragon")) {
                if (validMoves.size() != 0) {
                    shuffle(validMoves.begin(), validMoves.end(), rng);
                    pair<int, int> newCoords = validMoves.at(0);
                    shared_ptr<Tile> nextTile = curFloor->getTile(newCoords.first, newCoords.second);
                    
                    nextTile->setType(Tile::ENEMY);
                    nextTile->setEnemy(enemy);
                    enemy->setPos(newCoords.first, newCoords.second);
                    curFloor->getTile(curX, curY)->setType(Tile::EMPTY);
                    curFloor->getTile(curX, curY)->setEnemy(nullptr);
                }
            }
	    }
        // Reset dragon's hostility
        if (enemy->getName() == "Dragon") {
            enemy->resetHostile();
        }
	    enemy->setMoved();
	}
}

void Game::enemyRound() {
	shared_ptr<Floor> curFloor = getFloor(currentFloor);
    string empty = "";  
    setEnemyCommandLine(empty); 
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
