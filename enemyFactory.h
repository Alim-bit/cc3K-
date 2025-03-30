#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H
#include <string>
#include <memory>

#include "enemy.h"

class EnemyFactory {

public:
    // returns a random enemy (excluding dragon)
    static std::shared_ptr<Enemy> createEnemy(std::string name);
    
};

#endif