#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H
#include <string>
#include <memory>

#include "playerChar.h"

class GameFactory {

public:
    // returns a race specific player, if race is invalid then returns nullptr
    static std::shared_ptr<PlayerChar> createPlayer( const std::string &race );
};

#endif
