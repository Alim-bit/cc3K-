#include "playerChar.h"
#include <string>

using namespace std;

PlayerChar::PlayerChar( string name, int maxhp, int hp, int atk, int def, int floor ) 
: name{name}, MAXHP{maxhp}, HP{hp}, ATK{atk}, DEF{def}, floor{floor} {}

int PlayerChar::getHP() { return HP; }

int PlayerChar::getFloor() { return floor; }
