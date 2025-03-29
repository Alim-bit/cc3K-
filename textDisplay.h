#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <iostream>
#include <memory>
#include "observer.h"
#include "game.h"
using namespace std;

class TextDisplay: public Observer {
    shared_ptr<Game> subject;

public:
    TextDisplay(shared_ptr<Game> s);
    ~TextDisplay();
    void notify() override;
};

#endif
