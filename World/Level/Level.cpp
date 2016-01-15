//
// Created by pawkrol on 11/27/15.
//

#define PLAYER_SPAWN 255
#define BLOCK 199
#define DOOR 155
#define LEVER 150
#define TILE 100
#define PICKLE_SPAWNER 50
#define RAT_SPAWNER 10
#define COLLECTABLE 0

#include <SFML/Graphics/Image.hpp>

#include "Level.h"
#include "Lights/LightSource.h"
#include "Elements/Block.h"
#include "../../framework/GameException.h"
#include "Elements/RatSpawner.h"
#include "../CollectableHP.h"
#include "../CollectableStamina.h"
#include "Elements/PickleSpawner.h"

Level::Level(int width, int height)
        : tiles(2, std::vector< Tile * >((unsigned long) width * height)){

    this->width = width;
    this->height = height;
}

void Level::init(){
    for (int y = 0; y < height; ++y ){
        for (int x = 0; x < width; ++x ){
            tiles[0][x + y * width] = nullptr;
            tiles[1][x + y * width] = nullptr;
        }
    }
}

void Level::initLights(Player *player){
    playerLight = new LightSource(this);
    playerLight->setLightSource(player);
    playerLight->setLightDistance(player->getViewDistance());
    playerLight->update();
}

bool Level::load(std::string levelFile) {
    init();

    sf::Image level;
    if (!level.loadFromFile(levelFile)){
        throw GameException("Exception: Can't load level");
    }

    sf::Color color;
    for (unsigned int y = 0; y < (unsigned int) height; ++y ){
        for (unsigned int x = 0; x < (unsigned int) width; ++x ){
            color = level.getPixel(x, y);

            switch (color.r){
                case BLOCK:
                    tiles[1][x + y * width] = new Block(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    obstacles.push_back(tiles[1][x + y * width]);
                    break;

                case TILE:
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    break;

                case LEVER:
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    leverToDoorID[color.g] =
                            new Lever(x * Tile::WIDTH/2, y * Tile::HEIGHT/2, true, nullptr);
                    break;

                case DOOR:
                    Doors::Side side;
                    if (color.b == 1) side = Doors::Side::DOWN;
                    else if (color.b == 2) side = Doors::Side::UP;
                    else if (color.b == 3) side = Doors::Side::LEFT;
                    else side = Doors::Side::RIGHT;

                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    tiles[1][x + y * width] = new Doors(x * Tile::WIDTH/2, y * Tile::HEIGHT/2,
                                                        side, true, color.g);

                    doors.push_back((Doors *)tiles[1][x + y * width]);
                    obstacles.push_back(tiles[1][x + y * width]);

                    break;

                case COLLECTABLE:
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    if (color.g == 10) {
                        obstacles.push_back(new CollectableHP(x * Tile::WIDTH/2, y * Tile::HEIGHT/2));
                    } else if (color.g == 50){
                        obstacles.push_back(new CollectableStamina(x * Tile::WIDTH/2, y * Tile::HEIGHT/2));
                    }
                    break;

                case RAT_SPAWNER:
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    entities.push_back(new RatSpawner(x * Tile::WIDTH/2, y * Tile::HEIGHT/2));
                    break;

                case PICKLE_SPAWNER:
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    entities.push_back(new PickleSpawner(x * Tile::WIDTH/2, y * Tile::HEIGHT/2));
                    break;

                case PLAYER_SPAWN:
                    playerSpawn.x = x * Tile::WIDTH/2 + Tile::WIDTH/4;
                    playerSpawn.y = y * Tile::HEIGHT/2 + Tile::HEIGHT/4;
                    tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                    break;

                default:
                    break;
            }
        }
    }

    for(auto const& id : leverToDoorID){
        id.second->setDoors(getDoorById(id.first));
        actionObjects.push_back(id.second);
    }

    leverToDoorID.clear();

    return true;
}

void Level::update() {
    for (int y = 0; y < height; ++y ){
        for (int x = 0; x < width; ++x ){
            if (tiles[0][x + y * width] != nullptr) {
                tiles[0][x + y * width]->update();
            }
            if (tiles[1][x + y * width] != nullptr) {
                tiles[1][x + y * width]->update();
            }
        }
    }

    playerLight->update();
}

void Level::render(int layer, sf::RenderWindow *w, Camera *c) {
    renderLayer(layer, w, c);
}

Tile* Level::getTile(int layer, sf::Vector2i pos) {
    int index = pos.x + pos.y * width;
    if (index > -1 && index < width*height)
        return tiles[layer][index];
    else
        return nullptr;
}

Tile* Level::getTile(int layer, int x, int y) {
    int index = x + y * width;
    if (index > -1 && index < width*height)
        return tiles[layer][index];
    else
        return nullptr;
}

sf::Vector2i Level::getSize() {
    return sf::Vector2i(width, height);
}

void Level::setTile(sf::Vector2i pos, int layer, Tile *tile) {
    int index = pos.x + pos.y * width;
    tiles[layer][index] = tile;
}

std::vector<Renderable *> Level::getObstacles() {
    return obstacles;
}

std::vector<Renderable *> Level::getGroundTilesAround(sf::Vector2f pos) {
    std::vector<Renderable *> obstacles;
    Tile *tile;

    pos.x /= (Tile::WIDTH/2);
    pos.y /= (Tile::HEIGHT/2);

    pos.x += 1;
    pos.y += 1;

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if ( i != 0 || j != 0 ){
                int x = (int)pos.x + j;
                int y = (int)pos.y + i;
                tile = getTile(0, x, y);

                if ( tile != nullptr ) {
                    obstacles.push_back(tile);
                }
            }
        }
    }

    return obstacles;
}

sf::Vector2f Level::getPlayerSpawnPoint() {
    return playerSpawn;
}

std::vector<Entity *> Level::getEntities() {
    return entities;
}

std::vector<Renderable *> Level::getActionObjects() {
    return actionObjects;
}

void Level::renderLayer(int layer, sf::RenderWindow *w, Camera *c) {
    for (int y = 0; y < height; ++y ){
        for (int x = 0; x < width; ++x ){
            if (tiles[layer][x + y * width] != NULL) {
                tiles[layer][x + y * width]->render(w, c);
            }
        }
    }
}

LightSource* Level::getLightSource() {
    return playerLight;
}

Doors* Level::getDoorById(int id) {
    for (Doors *d : doors){
        if (d->id == id){
            return d;
        }
    }
    return nullptr;
}

Tile* Level::operator()(int layer, int element) {
    return tiles[layer][element];
}

Level::~Level() {
    for ( tilesLayers t : tiles ) {
        t.clear();
    }
    tiles.clear();
}