#include "playerChar.h"
#include <string>

using namespace std;

PlayerChar::PlayerChar( string race, int maxhp, int hp, int atk, int def, int floor ) 
: race{race}, MAXHP{maxhp}, HP{hp}, ATK{atk}, DEF{def} {}

int PlayerChar::getHP() { return HP; }

int PlayerChar::getATK() { return ATK; }

int PlayerChar::getDEF() { return DEF; }

string PlayerChar::getRace() { return race; }


