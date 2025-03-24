#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H
#include <string>

class PlayerChar {

protected:
    std::string name;
    int MAXHP;
    int HP;
    int ATK;
    int DEF;
    int floor;

public:
    PlayerChar( std::string name, int maxhp, int hp, int atk, int def, int floor );
    virtual ~PlayerChar() = default;
    // virtual void playerAbility() = 0;

    int getHP();
    int getFloor();
};

#endif
