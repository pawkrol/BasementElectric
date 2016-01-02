//
// Created by pawkrol on 12/1/15.
//

#include "InputHandler.h"
#include "Commands/MoveUpCommand.h"
#include "Commands/MoveDownCommand.h"
#include "Commands/MoveLeftCommand.h"
#include "Commands/MoveRightCommand.h"
#include "Commands/HitCommand.h"

InputHandler::InputHandler() {
    buttonD = new MoveRightCommand();
    buttonA = new MoveLeftCommand();
    buttonW = new MoveUpCommand();
    buttonS = new MoveDownCommand();
    buttonReturn = new HitCommand();
}

Command* InputHandler::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        return this->buttonReturn;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        return this->buttonW;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        return this->buttonS;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        return this->buttonA;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        return this->buttonD;
    }

    return nullptr;
}

void InputHandler::clear() {
    delete buttonW;
    delete buttonA;
    delete buttonS;
    delete buttonD;
    delete buttonReturn;
}