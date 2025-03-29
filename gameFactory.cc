#include "gameFactory.h"
#include <string>
#include <memory>

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"

using namespace std;

shared_ptr<PlayerChar> GameFactory::createPlayer( const string &race ) {
    if (race == "h") { return make_shared<Human>(); }
    else if (race == "d") { return make_shared<Dwarf>(); }
    else if (race == "e") { return make_shared<Elf>(); }
    else if (race == "o") { return make_shared<Orc>(); }
    else { return nullptr; }
}
