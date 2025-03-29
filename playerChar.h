#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H
#include <string>

class PlayerChar {

protected:
    std::string race;
    int MAXHP;
    int HP;
    int ATK;
    int DEF;

public:
    PlayerChar( std::string race, int maxhp, int hp, int atk, int def, int floor );
    virtual ~PlayerChar() = default;
    // virtual void playerAbility() = 0;

    int getHP();
    int getATK();
    int getDEF();
    std::string getRace();
};

#endif
