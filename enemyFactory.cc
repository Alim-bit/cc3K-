#include "enemyFactory.h"
#include <string>
#include <memory>

#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "troll.h"
#include "merchant.h"
#include "phoenix.h"
#include "dragon.h"

using namespace std;

shared_ptr<Enemy> EnemyFactory::createEnemy(string name) {
    
    if (name == "Werewolf") { return make_shared<Werewolf>(); }
    else if (name == "Vampire") { return make_shared<Vampire>(); }
    else if (name == "Goblin") { return make_shared<Goblin>(); }
    else if (name == "Troll") { return make_shared<Troll>(); }
    else if (name == "Phoenix") { return make_shared<Phoenix>(); }
    else if (name == "Merchant") { return make_shared<Merchant>(); }
    else { return make_shared<Dragon>(); }

}
