//
// Created by pawkrol on 11/27/15.
//

#include <assert.h>
#include <fstream>
#include "ScreenComponent.h"
#include "GameException.h"

//PRIVATE
ScreenComponent::ScreenComponent() { }

void ScreenComponent::createWindow() {
    if (window == nullptr) {
        try {
            loadSettings();
        } catch (GameException &e){
            std::cout << e.what() << std::endl;
            std::cout << "Default setting loaded" << std::endl;
        }

        window = new sf::RenderWindow(sf::VideoMode(width, height), "Basement Electric",
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
            try {
                saveSettings();
            } catch (GameException &e){
                std::cout << e.what() << std::endl;
            }
            closeWindow();
        }
    }
}

void ScreenComponent::saveSettings() {
    std::ofstream settings;
    settings.open("/home/pawkrol/Documents/settings.be", std::ios::out | std::ios::trunc);

    if (!settings.is_open()){
        throw GameException("Exception: Can't save settings!");
    }

    settings << width << std::endl << height;

    settings.close();
}

void ScreenComponent::loadSettings() {
    std::ifstream settings;
    settings.open("/home/pawkrol/Documents/settings.be", std::ios::in );

    if (!settings.is_open()){
        throw GameException("Exception: Can't load settings!");
    }

    settings >> width;
    settings >> height;

    settings.close();
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

        window->clear(sf::Color(16, 18, 11));

        gameContainer->update();
        gameContainer->render(window);

        window->display();
    }
}

ScreenComponent::~ScreenComponent() {
    delete gameContainer;
    delete window;
}