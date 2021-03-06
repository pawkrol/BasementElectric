//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_INPUTHANDLER_H
#define DUDESPATROL_INPUTHANDLER_H


#include <SFML/Window/Event.hpp>

#include "Commands/Command.h"

class InputHandler {
private:
    Command *buttonW;
    Command *buttonD;
    Command *buttonS;
    Command *buttonA;
    Command *buttonE;
    Command *buttonReturn;
    Command *buttonSpace;

    sf::Event event;

public:
    InputHandler();

    Command* handleInput();

    void clear();
};


#endif //DUDESPATROL_INPUTHANDLER_H
