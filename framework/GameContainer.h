//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_GAMECOINTAINER_H
#define DUDESPATROL_GAMECOINTAINER_H

#include <vector>

#include "../include/Renderable.h"
#include "Camera.h"
#include "Input/InputHandler.h"
#include "../Player.h"
#include "../World/Level/Level.h"

class GameContainer {
private:
    std::vector<Renderable*> Renderables;

    Level *level;
    Camera *camera;
    Command *command;

    Player *player;

    InputHandler inputHandler;

public:
    GameContainer();
    ~GameContainer();

    bool init();
    void update();
    void render(sf::RenderWindow *w);

    void addRenderable(Renderable *element);
    bool removeRenderable(Renderable *element);

    void createCamera(sf::RenderWindow *w);
};


#endif //DUDESPATROL_GAMECOINTAINER_H
