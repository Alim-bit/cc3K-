#include "enemy.h"
#include <string>

using namespace std;

Enemy::Enemy( string name, char symbol, int maxhp, int hp, int atk, int def )
: name{name}, symbol{symbol}, MAXHP{maxhp}, HP{hp}, ATK{atk}, DEF{def}, x{0}, y{0}, hasMoved{false} {}

int Enemy::getHP() { return HP; }

int Enemy::getATK() { return ATK; }

int Enemy::getDEF() { return DEF; }

string Enemy::getName() { return name; }

char Enemy::getSymbol() { return symbol; }

bool Enemy::getMoved() { return hasMoved; }

bool Enemy::isHostile() { return true; }

void Enemy::setHP(int newHP) {
    HP = newHP;
}

void Enemy::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}

void Enemy::setMoved() {
    hasMoved = true; 
}

void Enemy::resetMoved() {
    hasMoved = false;
}
