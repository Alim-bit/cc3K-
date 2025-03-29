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

    int x, y;
    bool inPassage;

public:
    PlayerChar(std::string race, int maxhp, int hp, int atk, int def, int floor);
    virtual ~PlayerChar() = default;
    // virtual void playerAbility() = 0;

    int getHP();
    int getATK();
    int getDEF();
    std::string getRace();

    void setHP(int newHP);
    void setPos(int newX, int newY);
    int getX();
    int getY();
    bool isInPassage();
    void setInPassage(bool inout);
};

#endif
