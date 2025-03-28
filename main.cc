#include <iostream>
#include <string>

#include "playerChar.h"
#include "game.h"
#include "textDisplay.h"
#include "gameFactory.h"

using namespace std;

int main() {      // will need cmd line args at some point

    while (true) {
        cout << "Choose your character's race from the following:" << endl;
        cout << "Human (h), Dwarf (d), Elf (e), Orc (o), or Quit." << endl;
        cout << "My choice:" << endl;

        string race;
        cin >> race;

        if (race == "Quit") { break; }
        shared_ptr<PlayerChar> player = GameFactory::createPlayer(race);
        
        if (!player) {
            cout << "Unidentified race, please try again." << endl;
            continue;
        }

        shared_ptr<Game> mainGame = make_shared<Game>(player);
        shared_ptr<TextDisplay> td = make_shared<TextDisplay>(mainGame);
        mainGame->initFloor();
        mainGame->displayGame();

        string command;
        while (cin >> command) { // GAME SIM
            
            // game commands

            // MOVE
            if (command == "no" || command == "so" || command == "ea" || command == "we"
                || command == "ne" || command == "nw" || command == "se" || command == "sw") {
                
                mainGame->move(command);

            // USE POTION IN DIRECTION
            } else if (command == "u") {
                cin >> command;

                // implement use potion method

            // ATTACK ENEMY IN DIRECTION
            } else if (command == "a") {
                cin >> command;

                // implement attack method

            // QUIT/RESTART
            } else if (command == "q" || command == "r") {
                break;

            // INVALID COMMAND
            } else {
                cout << "Invalid option, try again." << endl;
                continue;
            }

            // end game clauses
            if (mainGame->getCurrentFloor() > 5) {
                cout <<"Congratulations, you have beaten the game!" << endl;
                break;
            }

            if (player->getHP() <= 0) {
                cout << "You have been slain." << endl;
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