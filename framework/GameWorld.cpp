//
// Created by pawkrol on 11/27/15.
//

#include "GameWorld.h"
#include "GameException.h"
#include "DeadScreen.h"
#include "../World/CollectableStamina.h"
#include "../World/CollectableHP.h"
#include "../World/Level/Elements/Lever.h"
#include "../World/Mobs/MadPickle.h"

WorldResourceManager* GameWorld::wrm;

GameWorld::GameWorld() { }

bool GameWorld::init() {
    try {
        wrm = new WorldResourceManager();

        level = new Level(32, 32);
        level->load("res/level4.png");
    } catch (GameException &e){
        printf(e.what());
    }

    sf::Vector2f spawn = level->getPlayerSpawnPoint();
    player = new Player(spawn.x, spawn.y, 32, 32);
    addEntity(player);

    addEntities(level->getEntities());
    addObstacles(level->getObstacles());
    addActionObjects(level->getActionObjects());

    level->initLights(player);
    effects = new LevelEffects(level);

    userInterface.init(player);

    return true;
}

void GameWorld::update() {

    if (player->getHP() > 0) {
        command = inputHandler.handleInput();
        if (command) {
            command->execute(*player);
            command = nullptr;
        }
    }

    for (Entity *e : entityQueue){
        addEntity(e);
    }
    entityQueue.clear();

    for (Entity *ge : groundEntities){
        ge->update(this);
    }

    for (Renderable *e : entities){
        ((Entity*)e)->update(this);
    }

    for (Renderable *r : renderables){
        r->update();
    }

    for (Renderable *r : actionObjects){
        ((ActionObject*) r)->update(this);
    }

    camera->update(player->x, player->y);

    level->update();
    effects->update();

    userInterface.update();
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

    w->setView(w->getDefaultView());

    userInterface.render(w);

    if (player->getHP() <= 0) {
        DeadScreen deadScreen(w);
        deadScreen.render(w, camera);
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

std::vector<Renderable *> GameWorld::getClosest(Entity *entity, float range,
                                                std::vector<Renderable *> vec) {
    std::vector<Renderable *> closestObstacles;

    entity->toCarCords();
    float ex = entity->x;
    float ey = entity->y;
    entity->toIsoCords();

    double distance;

    for (auto *e : vec){
        e->toCarCords();
        float x = e->x;
        float y = e->y;
        e->toIsoCords();

        if (e != entity) {
            distance = sqrt((x - ex) * (x - ex) + (y - ey) * (y - ey));

            if (distance < range)
                closestObstacles.push_back(e);
        }
    }

    return closestObstacles;
}

std::vector<Renderable *> GameWorld::getClosestObstacles(Entity *entity, float range) {
    return getClosest(entity, range, obstacles);
}

std::vector<Renderable *> GameWorld::getClosestEntities(Entity *entity, float range) {
    return getClosest(entity, range, entities);
}

std::vector<Renderable *> GameWorld::getClosestActionObjects(Entity *entity, float range) {
    return getClosest(entity, range, actionObjects);
}

std::vector<Renderable *> GameWorld::getClosestGroundTiles(sf::Vector2f pos) {
    return level->getGroundTilesAround(pos);
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

void GameWorld::addActionObject(Renderable *renderable) {
    actionObjects.push_back(renderable);
    addObstacle(renderable);
}

void GameWorld::addActionObjects(std::vector<Renderable *> actionObjects) {
    this->actionObjects.insert(std::end(this->actionObjects),
                                        std::begin(actionObjects), std::end(actionObjects));
    addObstacles(actionObjects);
}

void GameWorld::removeActionObject(Renderable *renderable) {
    actionObjects.erase(
            std::remove(actionObjects.begin(), actionObjects.end(), renderable),
            actionObjects.end());
}

void GameWorld::addEntity(Entity *entity) {
    entities.push_back((Renderable *) entity);

    setUpRenderables();
}

void GameWorld::addEntities(std::vector<Entity *> entities) {
    this->entities.insert(std::end(this->entities),
                          std::begin(entities), std::end(entities));

    setUpRenderables();
}

void GameWorld::removeEntity(Renderable *renderable) {
    entities.erase(
            std::remove(entities.begin(), entities.end(), renderable),
            entities.end());
    setUpRenderables();
}

void GameWorld::addEntityQueue(Entity *entity) {
    entityQueue.push_back(entity);
}

void GameWorld::addObstacles(std::vector<Renderable *> obstacles) {
    this->obstacles.insert(std::end(this->obstacles),
                           std::begin(obstacles), std::end(obstacles));

    setUpRenderables();
}

void GameWorld::addObstacle(Renderable *obstacle) {
    obstacles.push_back(obstacle);
}

void GameWorld::removeObstacle(Renderable *obstacle) {
    obstacles.erase(
            std::remove(obstacles.begin(), obstacles.end(), obstacle),
            obstacles.end());
    setUpRenderables();
}

sf::Uint8 GameWorld::getGroundTileDarkness(float x, float y) {
    Tile *tile = level->getTile(0, (int)x, (int)y);
    if (tile == nullptr) return 255;
    else return tile->getDarkness();
}

LevelEffects* GameWorld::getLevelEffects() {
    return effects;
}

GameWorld::~GameWorld() {
    inputHandler.clear();

    delete wrm;
    delete player;
    delete level;
    delete camera;
}