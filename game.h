#ifndef GAME_H
#define GAME_H

#include "subject.h"
#include "floor.h"
#include "tile.h"
#include "playerChar.h"
#include <vector>
#include <memory>

class Game : public Subject {
    // a floors coords runs from (0, 0) to (24, 78)
    static const int MAXFLOORS = 5;
    vector<shared_ptr<Floor>> floors;
    shared_ptr<PlayerChar> player;

    int currentFloor;
    int goldScore;

    string commandLine;

public:
    Game(shared_ptr<PlayerChar> player) 
    : player{player}, currentFloor{1}, goldScore{0}, commandLine{"Player character has spawned."} {
        
        for(int i = 0; i < MAXFLOORS; ++i) {
            floors.push_back(make_shared<Floor>());
        }
    }

    void initFloor() {

        // assume coords are randomly generated
        int x = 10;
        int y = 5;

        getFloor(currentFloor)->getTile(x, y)->setType(Tile::PLAYER); // sets player spawn
        player->setPos(x, y);

        // init potions, enemies, and stairs
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
        displayGame();
    }

};


#endif
