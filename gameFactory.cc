#include "gameFactory.h"
#include <string>
#include <memory>

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"

using namespace std;

shared_ptr<PlayerChar> GameFactory::createPlayer( const string &race ) {
    if (race == "H") { return make_shared<Human>(); }
    else if (race == "D") { return make_shared<Dwarf>(); }
    else if (race == "E") { return make_shared<Elf>(); }
    else if (race == "O") { return make_shared<Orc>(); }
    else { return nullptr; }
}
