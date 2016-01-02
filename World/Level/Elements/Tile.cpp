//
// Created by pawkrol on 11/27/15.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Tile.h"

Tile::Tile() {
    this->x = 0;
    this->y = 0;
    this->width = WIDTH;
    this->height = HEIGHT;

    this->darkness = 255;

    init();
}

Tile::Tile(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = WIDTH;
    this->height = HEIGHT;

    this->darkness = 0;

    init();
}

void Tile::init() {
    if (!texture.loadFromFile("res/tile.png")){
        std::cout << "CAN'T LOAD TILE TEXTURE" << std::endl;
    }

    toIsoCords();
    setPosition(x, y);
    create();
    updateDarkness();
}

void Tile::update() {
    setDarkness(defaultDarkness);
}

void Tile::render(sf::RenderWindow *w, Camera *c) {
    toCarCords();
    if ( isInWindow(c) ) {
        toIsoCords();
        w->draw(*this);
    } else {
        toIsoCords();
    }
}

bool Tile::isInWindow(Camera *c) {
    sf::Vector2f fovS = c->getSize();
    sf::Vector2f fovC = c->getCenter();
    float zoom = c->getZoom();

    bool isX = (x <= fovC.x + (fovS.x/zoom)/2) && (x >= fovC.x - (fovS.x/zoom)/2);
    bool isY = (y <= fovC.y + (fovS.y/zoom)/2) && (y >= fovC.y - (fovS.y/zoom)/2);

    return isX && isY;
}

void Tile::setDarkness(sf::Uint8 darkness) {
    this->darkness = darkness;
    updateDarkness();
}

sf::Uint8 Tile::getDarkness() {
    return darkness;
}

void Tile::updateDarkness() {
    vertexArray[0].color = sf::Color(darkness, darkness, darkness, 255);
    vertexArray[1].color = sf::Color(darkness, darkness, darkness, 255);
    vertexArray[2].color = sf::Color(darkness, darkness, darkness, 255);
    vertexArray[3].color = sf::Color(darkness, darkness, darkness, 255);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertexArray, states);
}

void Tile::create() {
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(4);

    vertexArray[0].position = sf::Vector2f(x, y);
    vertexArray[1].position = sf::Vector2f((x + WIDTH), y);
    vertexArray[2].position = sf::Vector2f((x + WIDTH), (y + HEIGHT));
    vertexArray[3].position = sf::Vector2f(x, (y + HEIGHT));

    vertexArray[0].texCoords = sf::Vector2f(0, 0);
    vertexArray[1].texCoords = sf::Vector2f(WIDTH, 0);
    vertexArray[2].texCoords = sf::Vector2f(WIDTH, HEIGHT);
    vertexArray[3].texCoords = sf::Vector2f(0, HEIGHT);

}
