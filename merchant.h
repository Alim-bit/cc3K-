#ifndef MERCHANT_H
#define MERCHANT_H
#include <string>

#include "enemy.h"

class Merchant : public Enemy {
    // controls whether all merchants attack the player
    inline static bool hostile = false;

  public:
    Merchant();
    
    void makeHostile();
    bool isHostile();
};

#endif
