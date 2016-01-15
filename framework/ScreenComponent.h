//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_SCREENCOMPONENT_H
#define DUDESPATROL_SCREENCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "GameWorld.h"

class ScreenComponent {
private:
    ScreenComponent();

    unsigned int width;
    unsigned int height;

    sf::RenderWindow *window;
    sf::Event event;

    GameWorld *gameContainer;

    void createWindow();
    void closeWindow();
    void checkWindowEvent();

    void loadSettings();
    void saveSettings();

public:
    ScreenComponent(unsigned int width, unsigned int height);
    ~ScreenComponent();

    void init();
    void run();
};


#endif //DUDESPATROL_SCREENCOMPONENT_H
