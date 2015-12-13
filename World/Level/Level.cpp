//
// Created by pawkrol on 11/27/15.
//

#include <SFML/Graphics/Image.hpp>

#include "Level.h"
#include "Lights/LightSource.h"
#include "Elements/Block.h"

Level::Level(int width, int height) {
    this->width = width;
    this->height = height;
}

void Level::init(){
    tiles = new Tile**[2];
    tiles[0] = new Tile*[width * height];
    tiles[1] = new Tile*[width * height];
    for (int y = 0; y < height; ++y ){
        for (int x = 0; x < width; ++x ){
            tiles[0][x + y * width] = NULL;
            tiles[1][x + y * width] = NULL;
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
        return false;
    }

    sf::Color color;
    for (int y = 0; y < height; ++y ){
        for (int x = 0; x < width; ++x ){
            color = level.getPixel(x, y);

            if (color == sf::Color::Black){
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/4, y * Tile::HEIGHT/4);
            }

            if (color == sf::Color::Red){
                playerSpawn.x = x * Tile::WIDTH/2;
                playerSpawn.y = y * Tile::HEIGHT/2;
                tiles[0][x + y * width] = new Tile(x * Tile::WIDTH/4, y * Tile::HEIGHT/4);
            }

            if (color == sf::Color::Blue){
                tiles[1][x + y * width] = new Block(x * Tile::WIDTH/4, y * Tile::HEIGHT/4);
            }

        }
    }

    return true;
}

void Level::update() {
    playerLight->update();
}

void Level::render(int layer, sf::RenderWindow *w, Camera *c) {
    renderLayer(layer, w, c);
}

Tile* Level::getTile(sf::Vector2i pos) {
    int index = pos.x + pos.y * width;
    if (index < width*height)
        return tiles[0][index];
    else
        return NULL;
}

Tile* Level::getTile(int x, int y) {
    int index = x + y * width;
    if (index < width*height)
        return tiles[0][index];
    else
        return NULL;
}

sf::Vector2i Level::getSize() {
    return sf::Vector2i(width, height);
}

void Level::setTile(sf::Vector2f pos, Tile tile) {
}

sf::Vector2f Level::getPlayerSpawnPoint() {
    return playerSpawn;
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

Tile* Level::operator()(int layer, int element) {
    return tiles[layer][element];
}