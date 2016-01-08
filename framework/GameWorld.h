//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_GAMECOINTAINER_H
#define DUDESPATROL_GAMECOINTAINER_H

#include <vector>

#include "Camera.h"
#include "Input/InputHandler.h"
#include "../World/Level/Level.h"
#include "../World/Level/Elements/RatSpawner.h"
#include "../World/Rat.h"
#include "../include/GroundEntity.h"
#include "UserInterface.h"
#include "../World/Level/Effects/LevelEffects.h"

class GameWorld {
private:
    std::vector<Renderable*> renderables;
    std::vector<Renderable*> obstacles;
    std::vector<Renderable*> entities;
    std::vector<GroundEntity*> groundEntities;
    std::vector<Renderable*> actionObjects;
    std::vector<Entity *> entityQueue;

    Level *level;
    LevelEffects *effects;
    Camera *camera;
    Command *command;

    Player *player;

    RatSpawner *ratSpawner;

    InputHandler inputHandler;
    UserInterface userInterface;

    void addRenderable(Renderable *renderable);
    void addRenderables(std::vector<Renderable *> renderables);
    void setUpRenderables();
    void sortRenderables();

    std::vector<Renderable *> getClosest(Entity *entity, float range,
                                         std::vector<Renderable *> vec);

public:
    static WorldResourceManager *wrm;

    GameWorld();
    ~GameWorld();

    bool init();
    void update();
    void render(sf::RenderWindow *w);

    std::vector<Renderable *> getClosestObstacles(Entity *entity, float range);
    std::vector<Renderable *> getClosestEntities(Entity *entity, float range);
    std::vector<Renderable *> getClosestActionObjects(Entity *entity, float range);
    std::vector<Renderable *> getClosestGroundTiles(sf::Vector2f pos);

    void addObstacles(std::vector<Renderable *> obstacles);
    void addObstacle(Renderable *obstacle);
    void removeObstacle(Renderable *obstacle);

    void addEntity(Entity *entity);
    void removeEntity(Renderable *renderable);
    void addEntityQueue(Entity *entity);

    void addGroundEntity(GroundEntity *entity);
    void removeGroundEntity(GroundEntity *entity);

    void addActionObject(Renderable *renderable);
    void removeActionObject(Renderable *renderable);

    Player* getPlayer();

    sf::Uint8 getGroundTileDarkness(float x, float y);

    LevelEffects* getLevelEffects();

    void createCamera(sf::RenderWindow *w);
};


#endif //DUDESPATROL_GAMECOINTAINER_H
