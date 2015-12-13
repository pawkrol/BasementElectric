//
// Created by pawkrol on 11/27/15.
//

#include "../include/Renderable.h"
#include "GameContainer.h"

GameContainer::GameContainer() { }

void GameContainer::addRenderable(Renderable *element) {
    Renderables.push_back(element);
}

bool GameContainer::removeRenderable(Renderable *element) {
    for (Renderable *e: Renderables){
//        if (e == element){ //TODO: Override == operator
//
//        }
    }
}

bool GameContainer::init() {
    level = new Level(32, 32);
    if (!level->load("res/level2.png")){
        return false;
    }

    sf::Vector2f spawn = level->getPlayerSpawnPoint();
    player = new Player(spawn.x, spawn.y);
    level->initLights(player);

    for (Renderable *r: Renderables){
        r->init();
    }

    return true;
}

void GameContainer::update() {
    command = inputHandler.handleInput();
    if (command){
        command->execute(*player);
        command = NULL;
    }

    player->update();
    camera->update(player->x, player->y);
    level->update();

    for (Renderable *r: Renderables){
        r->update();
    }
}

void GameContainer::render(sf::RenderWindow *w) { //TODO: This is just temp, add depth sorting etc.
    level->render(0, w, camera);
    player->render(w, camera);
    level->render(1, w, camera);

    for (Renderable *r: Renderables){
        r->render(w, camera);
    }
}

void GameContainer::createCamera(sf::RenderWindow *w) {
    sf::Vector2u cameraSize = w->getSize();
    sf::Vector2f size(cameraSize.x, cameraSize.y);
    sf::Vector2f center(0, 0);
    camera = new Camera(w, size, center);
}

GameContainer::~GameContainer() {
    inputHandler.clear();
    delete camera;
}