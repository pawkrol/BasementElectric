//
// Created by pawkrol on 11/27/15.
//

#include "GameWorld.h"
#include "GameException.h"

GameWorld::GameWorld() { }

bool GameWorld::init() {
    try {
        level = new Level(32, 32);
        level->load("res/level2.png");

        sf::Vector2f spawn = level->getPlayerSpawnPoint();
        player = new Player(spawn.x, spawn.y, 32, 32);

        sf::Vector2f ratSpawn = level->getRatSpawnerPoint();
        ratSpawner = new RatSpawner(ratSpawn.x, ratSpawn.y);

    } catch (GameException &e){
        printf(e.what());
    }

    level->initLights(player);

    addObstacles(level->getObstacles());
    addEntity(player);
    addEntity(ratSpawner);

    return true;
}

void GameWorld::update() {
    command = inputHandler.handleInput();
    if (command){
        command->execute(*player);
        command = nullptr;
    }

    for (Entity *ge : groundEntities){
        ge->update(this);
    }

    for (Renderable *e : entities){
        ((Entity*)e)->update(this);
    }

    camera->update(player->x, player->y);
    level->update();
}

void GameWorld::render(sf::RenderWindow *w) {
    sortRenderables();

    level->render(0, w, camera);

    for (Entity *ge : groundEntities){
        ge->render(w, camera);
    }

    for (Renderable *r: renderables){
        r->render(w, camera);
    }
}

void GameWorld::createCamera(sf::RenderWindow *w) {
    sf::Vector2u cameraSize = w->getSize();
    sf::Vector2f size(cameraSize.x, cameraSize.y);
    sf::Vector2f center(0, 0);
    camera = new Camera(w, size, center);
}

void GameWorld::sortRenderables() {
    std::sort(renderables.begin(), renderables.end(),
              [](Renderable *a, Renderable *b) -> bool {
                  return a->x < b->x;
              });

    std::sort(renderables.begin(), renderables.end(),
              [](Renderable *a, Renderable *b) -> bool {
                  return a->y < b->y;
              });
}

Player* GameWorld::getPlayer(){
    return player;
}

std::vector<Renderable *> GameWorld::getClosestObstacles(Entity *entity) {
    return level->getObstaclesAround(entity);
}

std::vector<Renderable *> GameWorld::getClosestEntities(Entity *entity, float range) {
    std::vector<Renderable *> closestEntities;

    entity->toCarCords();
        float ex = entity->x;
        float ey = entity->y;
    entity->toIsoCords();

    double distance;

    for (auto *e : entities){
        e->toCarCords();
            float x = e->x;
            float y = e->y;
        e->toIsoCords();

        if (e != entity) {
            distance = sqrt((x - ex) * (x - ex) + (y - ey) * (y - ey));

            if (distance < range)
                closestEntities.push_back(e);
        }
    }

    return closestEntities;
}

void GameWorld::addRenderable(Renderable *renderable) {
    renderables.push_back(renderable);
}

void GameWorld::addRenderables(std::vector<Renderable *> renderables) {
    this->renderables.insert(std::end(this->renderables),
                             std::begin(renderables), std::end(renderables));
}

void GameWorld::setUpRenderables() {
    if (!renderables.empty())
        renderables.clear();

    addRenderables(entities);
    addRenderables(obstacles);
}

void GameWorld::addGroundEntity(GroundEntity *entity) {
    groundEntities.push_back(entity);
}

void GameWorld::removeGroundEntity(GroundEntity *entity) {
    groundEntities.erase(
            std::remove(groundEntities.begin(), groundEntities.end(), entity),
            groundEntities.end());
}

void GameWorld::addEntity(Entity *entity) {
    entities.push_back((Renderable *) entity);

    setUpRenderables();
}

void GameWorld::removeEntity(Renderable *renderable) {
    entities.erase(
            std::remove(entities.begin(), entities.end(), renderable),
            entities.end());
    setUpRenderables();
}

void GameWorld::addObstacles(std::vector<Renderable *> obstacles) {
    this->obstacles.insert(std::end(this->obstacles),
                           std::begin(obstacles), std::end(obstacles));

    setUpRenderables();
}

sf::Uint8 GameWorld::getGroundTileDarkness(float x, float y) {
    return level->getTile(0, (int)x, (int)y)->getDarkness();
}

void GameWorld::addObstacle(Renderable *obstacle) {
    obstacles.push_back(obstacle);
}

GameWorld::~GameWorld() {
    inputHandler.clear();
    delete ratSpawner;
    delete player;
    delete level;
    delete camera;
}