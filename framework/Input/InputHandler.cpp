//
// Created by pawkrol on 12/1/15.
//

#include "InputHandler.h"
#include "Commands/MoveUpCommand.h"
#include "Commands/MoveDownCommand.h"
#include "Commands/MoveLeftCommand.h"
#include "Commands/MoveRightCommand.h"

InputHandler::InputHandler() {
    buttonD = new MoveRightCommand();
    buttonA = new MoveLeftCommand();
    buttonW = new MoveUpCommand();
    buttonS = new MoveDownCommand();
}

Command* InputHandler::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        return this->buttonW;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        return this->buttonS;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        return this->buttonA;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        return this->buttonD;
    }

    return nullptr;
}

void InputHandler::clear() {
    delete buttonW;
    delete buttonA;
    delete buttonS;
    delete buttonD;
}