//
// Created by pawkrol on 11/27/15.
//

#include "../include/Renderable.h"
#include "GameContainer.h"
#include "../World/Level/Elements/Block.h"
#include "GameException.h"

GameContainer::GameContainer() { }

void GameContainer::addRenderable(Renderable *element) {
    renderables.push_back(element);
}

void GameContainer::addRenderables(std::vector<Renderable *> obstacles) {
    renderables.insert(std::end(renderables),
                       std::begin(obstacles), std::end(obstacles));
}

bool GameContainer::removeRenderable(Renderable *element) {
    return false;
}

bool GameContainer::init() {
    try {
        level = new Level(32, 32);
        level->load("res/level2.png");

        sf::Vector2f spawn = level->getPlayerSpawnPoint();
        player = new Player(spawn.x, spawn.y, 32, 32);

    } catch (GameException &e){
        printf(e.what());
    }

    level->initLights(player);

    addRenderables(level->getObstacles());
    addRenderable(player);

    return true;
}

void GameContainer::update() {
    command = inputHandler.handleInput();
    if (command){
        command->execute(*player);
        command = nullptr;
    }

    player->update(level->getObstacles());

    camera->update(player->x, player->y);
    level->update();
}

void GameContainer::render(sf::RenderWindow *w) {
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