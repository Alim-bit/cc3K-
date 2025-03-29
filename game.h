#ifndef GAME_H
#define GAME_H

#include "subject.h"
#include "floor.h"
#include "playerChar.h"
#include <vector>
#include <memory>

class Game : public Subject {
    static const int MAXFLOORS = 5;
    vector<shared_ptr<Floor>> floors;
    shared_ptr<PlayerChar> player;

    int currentFloor;
    int goldScore;

public:
    Game(shared_ptr<PlayerChar> player) : player{player}, currentFloor{1}, goldScore{0} {
        
        for(int i = 0; i < MAXFLOORS; ++i) {
            floors.push_back(make_shared<Floor>());
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
};


#endif