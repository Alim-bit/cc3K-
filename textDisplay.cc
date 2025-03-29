#include "textDisplay.h"
#include <vector>
using namespace std;

struct ptrDeleter {
    void operator()(void const *) const {
    }
};

TextDisplay::TextDisplay(shared_ptr<Game> s) : subject(s) {
    shared_ptr<Observer> o (this, ptrDeleter());
    subject->attach(o);
}

void TextDisplay::notify() {

    int floorNum = subject->getCurrentFloor();
    shared_ptr<Floor> currentFloor = subject->getFloor(floorNum);
    vector<vector<shared_ptr<Tile>>> tiles = currentFloor->getTiles();

    for(vector<shared_ptr<Tile>> row : tiles) {
        for(shared_ptr<Tile> tile : row) {
            cout << tile->getChar();
        }
        
        cout << endl;
    } 

    shared_ptr<PlayerChar> player = subject->getPlayer();

    cout << "Race: " << player->getRace() << " Gold: " << subject->getGoldScore() << "                                                  Floor " << floorNum << endl;
    cout << "HP: " << player->getHP() << endl;
    cout << "Atk: " << player->getATK() << endl;
    cout << "Def: " << player->getDEF() << endl;
    cout << "Action: " << subject->getCommandLine() << endl; 
}

TextDisplay::~TextDisplay() {
    shared_ptr<Observer> o (this, ptrDeleter());
    subject->detach(o);
}
