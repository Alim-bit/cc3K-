#include "gameFactory.h"
#include <string>
#include <memory>

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"

using namespace std;

unique_ptr<PlayerChar> GameFactory::createPlayer( const string &race ) {
    if (race == "H") { return make_unique<Human>(); }
    else if (race == "D") { return make_unique<Dwarf>(); }
    else if (race == "E") { return make_unique<Elf>(); }
    else if (race == "O") { return make_unique<Orc>(); }
    else { return nullptr; }
}
