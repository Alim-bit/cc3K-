#include "playerChar.h"
#include <string>

using namespace std;

PlayerChar::PlayerChar( string race, int maxhp, int hp, int atk, int def, int floor ) 
: race{race}, MAXHP{maxhp}, HP{hp}, ATK{atk}, DEF{def}, tempATKBonus{0}, tempDEFBonus{0},  x{0}, y{0}, inPassage{false}, barrierSuit{false} {}

int PlayerChar::getHP() { return HP; }

int PlayerChar::getATK() { return ATK; }

int PlayerChar::getDEF() { return DEF; }

int PlayerChar::getTempATK() { return tempATKBonus; }

int PlayerChar::getTempDEF() { return tempDEFBonus; }

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

void PlayerChar::drinkPotion(const std::string &potionType) {
    if (potionType == "RH") {
        HP += 10;
        if (HP > MAXHP) {
            HP = MAXHP;
        }
    } else if (potionType == "PH") {
        HP -= 10;
        if (HP < 0) {
            HP = 0;
        }
    } else if (potionType == "BA") {
        tempATKBonus += 5;
    } else if (potionType == "BD") {
        tempDEFBonus += 5;
    } else if (potionType == "WA") {
        if (ATK + tempATKBonus - 5 < 0)
            tempATKBonus = -ATK;
        else
            tempATKBonus -= 5;
    } else if (potionType == "WD") {
        if (DEF + tempDEFBonus - 5 < 0)
            tempDEFBonus = -DEF;
        else
            tempDEFBonus -= 5;
    }
}

void PlayerChar::resetTempPotions() {
    tempATKBonus = 0;
    tempDEFBonus = 0;
}

bool PlayerChar::hasBarrierSuit() {
    return barrierSuit;
}

void PlayerChar::setBarrierSuit() {
    barrierSuit = true;
}

