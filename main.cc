#include <iostream>
#include <string>

#include "playerChar.h"
#include "gameFactory.h"

using namespace std;

int main() {      // will need cmd line args at some point

    while (true) {
        cout << "Choose your character's race from the following:" << endl;
        cout << "Human (H), Dwarf (D), Elf (E), Orc (O), or Quit." << endl;
        cout << "My choice:" << endl;

        string race;
        cin >> race;

        if (race == "Quit") { break; }
        unique_ptr<PlayerChar> player = GameFactory::createPlayer(race);
        
        if (!player) {
            cout << "Unidentified race, please try again." << endl;
            continue;
        }

        string command;
        while (cin >> command) { // GAME SIM

            cout << "game is playing" << endl; // test

            // assume commands happen here



            //

            if (player->getFloor() > 5) {
                cout << "Congratulations! You have beaten the game." << endl;
                break;
            }

            if (player->getHP() <= 0) {
                cout << "You have been slain." << endl;
                break;
            }

            if (command == "q" || command == "r") {
                break;
            }
        }

        // ending bit
        if (command == "q") {
            break;
        } else if (command == "r") {
            continue;
        } else {
            cout << "Would you like to restart? Yes/No:" << endl;
            cin >> command;
            if (command == "Yes") { continue; }
            else { break; }
        }
    }

    return 0;
}