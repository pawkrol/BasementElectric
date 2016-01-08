//
// Created by pawkrol on 11/27/15.
//

#include <SFML/Graphics/Image.hpp>

#include "Level.h"
#include "Lights/LightSource.h"
#include "Elements/Block.h"
#include "../../framework/GameException.h"

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

            if (color == sf::Color::Black){
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
            }

            if (color == sf::Color::Red){
                playerSpawn.x = x * Tile::WIDTH/2 + Tile::WIDTH/4;
                playerSpawn.y = y * Tile::HEIGHT/2 + Tile::HEIGHT/4;
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
            }

            if (color == sf::Color::Blue){
                tiles[1][x + y * width] = new Block(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                obstacles.push_back(tiles[1][x + y * width]);
            }

            if (color == sf::Color::Green){
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                ratSpawner.x = x * Tile::WIDTH/2;
                ratSpawner.y = y * Tile::HEIGHT/2;
            }

            if (color == sf::Color::White){
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/2, y * Tile::HEIGHT/2);
                tiles[1][x + y * width] = new Doors(x * Tile::WIDTH/2, y * Tile::HEIGHT/2,
                                                    Doors::LEFT, true);
                doors.push_back((Doors *)tiles[1][x + y * width]);
                obstacles.push_back(tiles[1][x + y * width]);
            }

        }
    }

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

sf::Vector2f Level::getRatSpawnerPoint() {
    return ratSpawner;
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