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

shared_ptr<Enemy> EnemyFactory::createEnemy(int rand) {
    // generate # between 1-18 
    if (rand <= 4) { return make_shared<Werewolf>(); }
    else if (rand > 4 && rand < 8) { return make_shared<Vampire>(); }
    else if (rand > 7 && rand < 13) { return make_shared<Goblin>(); }
    else if (rand > 12 && rand < 15) { return make_shared<Troll>(); }
    else if (rand > 14 && rand < 17) { return make_shared<Phoenix>(); }
    else { return make_shared<Merchant>(); }
}

shared_ptr<Enemy> EnemyFactory::createDragon() {
    // Gets called when dragon hoard or Barrier Suit is spawned
    return make_shared<Dragon>();
}
