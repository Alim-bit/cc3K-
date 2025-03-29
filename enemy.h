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

public:
    Enemy(std::string name, char symbol, int maxhp, int hp, int atk, int def);
    virtual ~Enemy() = default;

    int getHP();
    int getATK();
    int getDEF();
    std::string getName();
    char getSymbol();
    bool getMoved();
    virtual bool isHostile();

    void setPos(int newX, int newY);
    int getX();
    int getY();
    void setMoved();
    void resetMoved();

};

#endif
