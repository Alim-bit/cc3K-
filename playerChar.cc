#include "playerChar.h"
#include <string>

using namespace std;

PlayerChar::PlayerChar( string race, int maxhp, int hp, int atk, int def, int floor ) 
: race{race}, MAXHP{maxhp}, HP{hp}, ATK{atk}, DEF{def}, x{0}, y{0}, inPassage{false} {}

int PlayerChar::getHP() { return HP; }

int PlayerChar::getATK() { return ATK; }

int PlayerChar::getDEF() { return DEF; }

string PlayerChar::getRace() { return race; }

void PlayerChar::setHP(int newHP) {
    HP = newHP;
}

void PlayerChar::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

int PlayerChar::getX() {
    return x;
}

int PlayerChar::getY() {
    return y;
}

bool PlayerChar::isInPassage() {
    return inPassage;
}

void PlayerChar::setInPassage(bool inout) {
    inPassage = inout;
}
