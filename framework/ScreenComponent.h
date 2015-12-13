//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_SCREENCOMPONENT_H
#define DUDESPATROL_SCREENCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "GameContainer.h"

class ScreenComponent {
private:
    ScreenComponent();

    int width;
    int height;

    sf::RenderWindow *window;
    sf::Event event;

    GameContainer *gameContainer;

    void createWindow();
    void closeWindow();
    void checkWindowEvent();

public:
    ScreenComponent(int width, int height);
    ~ScreenComponent();

    void init();
    void run();
};


#endif //DUDESPATROL_SCREENCOMPONENT_H
