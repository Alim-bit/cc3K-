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
    int tempATKBonus; 
    int tempDEFBonus; 
    int x, y;
    bool inPassage;
    bool barrierSuit;

public:
    PlayerChar(std::string race, int maxhp, int hp, int atk, int def, int floor);
    virtual ~PlayerChar() = default;

    int getHP();
    int getATK();
    int getDEF();
    int getTempATK();
    int getTempDEF();
    std::string getRace();

    void setHP(int newHP);
    void setPos(int newX, int newY);
    int getX();
    int getY();
    bool isInPassage();
    void setInPassage(bool inout);

    void drinkPotion(const std::string &potionType);
    void resetTempPotions();

    bool hasBarrierSuit();
    void setBarrierSuit();
};

#endif
