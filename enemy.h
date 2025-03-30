#ifndef ENEMY_H
#define ENEMY_H
#include <string>

class Enemy {

protected:
    std::string name;
    char symbol;
    int MAXHP;
    int HP;
    int ATK;
    int DEF;
  
    int x, y;
    bool hasMoved;
    bool holdingCompass;

public:
    Enemy(std::string name, char symbol, int maxhp, int hp, int atk, int def);
    virtual ~Enemy() = default;

    int getHP();
    int getATK();
    int getDEF();
    std::string getName();
    char getSymbol();
    bool getMoved();
    // for dragon and merchant
    virtual void makeHostile();
    //just for dragon
    virtual void resetHostile();
    virtual bool isHostile();

    void setHP(int newHP);
    void setPos(int newX, int newY);
    int getX();
    int getY();
    void setMoved();
    void resetMoved();
    void setHolding();
    bool getHolding();

};

#endif
