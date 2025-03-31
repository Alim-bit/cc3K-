#ifndef DRAGON_H
#define DRAGON_H
#include <string>

#include "enemy.h"

class Dragon : public Enemy {
    bool hostile;

public:
    Dragon();

    void resetHostile();
    void makeHostile();
    bool isHostile();

};

#endif
