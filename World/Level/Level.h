//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_LEVEL_H
#define DUDESPATROL_LEVEL_H

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Elements/Tile.h"
#include "../../Player.h"

//forward declaration
class LightSource;

class Level {
private:
    typedef std::vector< Tile * > tilesLayers;
    typedef std::vector< tilesLayers > tiledMap;
    tiledMap tiles;

    std::vector<Renderable *> obstacles;

    LightSource *playerLight;

    int width;
    int height;

    sf::Vector2f playerSpawn;

    void init();
    void renderLayer(int layer, sf::RenderWindow *w, Camera *c);

public:
    Level(int width, int height);

    bool load(std::string levelFile);
    void initLights(Player *player);
    void update();
    void render(int layer, sf::RenderWindow *w, Camera *c);

    void setTile(sf::Vector2i pos, int layer, Tile *tile);
    std::vector<Renderable *> getObstacles();

    Tile* getTile(sf::Vector2i pos);
    Tile* getTile(int x, int y);
    sf::Vector2i getSize();

    sf::Vector2f getPlayerSpawnPoint();

    Tile* operator()(int layer, int element);

    ~Level();
};


#endif //DUDESPATROL_LEVEL_H
