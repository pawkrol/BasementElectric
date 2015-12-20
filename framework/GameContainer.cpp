//
// Created by pawkrol on 11/27/15.
//

#include "../include/Renderable.h"
#include "GameContainer.h"

GameContainer::GameContainer() { }

void GameContainer::addRenderable(Renderable *element) {
    renderables.push_back(element);
}

bool GameContainer::removeRenderable(Renderable *element) {
//    for (Renderable *e: renderables){
//        if (e == element){ //TODO: Override == operator
//
//        }
//    }
    return false;
}

bool GameContainer::init() {
    level = new Level(32, 32);
    if (!level->load("res/level2.png")){
        return false;
    }

    sf::Vector2f spawn = level->getPlayerSpawnPoint();
    player = new Player(spawn.x, spawn.y);
    level->initLights(player);

    level->pushRenderables(renderables);
    addRenderable(player);

    return true;
}

void GameContainer::update() {
    command = inputHandler.handleInput();
    if (command){
        command->execute(*player);
        command = NULL;
    }

    for (Renderable *r: renderables){
        r->update();
    }

    camera->update(player->x, player->y);
    level->update();
}

void GameContainer::render(sf::RenderWindow *w) { //TODO: This is just temp, add depth sorting etc.
    sortRenderables();

    level->render(0, w, camera);

    for (Renderable *r: renderables){
        r->render(w, camera);
    }
}

void GameContainer::createCamera(sf::RenderWindow *w) {
    sf::Vector2u cameraSize = w->getSize();
    sf::Vector2f size(cameraSize.x, cameraSize.y);
    sf::Vector2f center(0, 0);
    camera = new Camera(w, size, center);
}

void GameContainer::sortRenderables() {
    std::sort(renderables.begin(), renderables.end(),
              [](Renderable *a, Renderable *b) -> bool {
                  return a->x < b->x;
              });

    std::sort(renderables.begin(), renderables.end(),
              [](Renderable *a, Renderable *b) -> bool {
                  return a->y < b->y;
              });
}

GameContainer::~GameContainer() {
    inputHandler.clear();
    delete camera;
}