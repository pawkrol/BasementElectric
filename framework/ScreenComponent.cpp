//
// Created by pawkrol on 11/27/15.
//

#include <assert.h>
#include "ScreenComponent.h"

//PRIVATE
ScreenComponent::ScreenComponent() { }

void ScreenComponent::createWindow() {
    if (window == nullptr) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), "DudesPatrol",
                                        sf::Style::None);
        window->setVerticalSyncEnabled(true);
        window->setMouseCursorVisible(false);
        window->setFramerateLimit(60);
    }
}

void ScreenComponent::closeWindow() {
    window->close();
}

void ScreenComponent::checkWindowEvent() {
    if (window->pollEvent(event)){
        if ((event.type == sf::Event::KeyPressed)
                    && (event.key.code == sf::Keyboard::Escape)){
            closeWindow();
        }
    }
}

//PUBLIC

ScreenComponent::ScreenComponent(unsigned int width, unsigned int height) : window(nullptr) {
    this->width = width;
    this->height = height;

    gameContainer = new GameWorld();
}

void ScreenComponent::init() {
    createWindow();
    gameContainer->createCamera(window);
    assert(gameContainer->init());
}

void ScreenComponent::run() {
    while (window->isOpen()) {

        checkWindowEvent();

        window->clear(sf::Color::Black);

        gameContainer->update();
        gameContainer->render(window);

        window->display();
    }
}

ScreenComponent::~ScreenComponent() {
    delete gameContainer;
    delete window;
}