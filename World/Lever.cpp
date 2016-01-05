//
// Created by pawkrol on 1/5/16.
//

#include "Lever.h"
#include "../framework/GameException.h"
#include "../framework/GameWorld.h"

Lever::Lever(float x, float y, bool isOn, Doors *door) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    this->_on = isOn;
    this->door = door;

    toIsoCords();
    init();
}

void Lever::init() {
    if (!texture.loadFromFile("res/lever.png")){
        throw GameException("Exception: Can't load lever texture");
    }

    onRect = sf::IntRect(0, 0, 32, 32);
    offRect = sf::IntRect(32, 0, 32, 32);

    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    if (_on) {
        sprite.setTextureRect(onRect);
    } else {
        sprite.setTextureRect(offRect);
    }
}

void Lever::update(GameWorld *world) {
    toCarCords();
    float mx = x / (Tile::WIDTH / 2);
    float my = y / (Tile::HEIGHT / 2);
    toIsoCords();

    darkness = world->getGroundTileDarkness(mx, my);

    sprite.setColor(sf::Color(darkness, darkness, darkness));
}

void Lever::render(sf::RenderWindow *w, Camera *c) {
    w->draw(sprite);
}

bool Lever::isOn() {
    return _on;
}

void Lever::action() {
    _on = !_on;

    door->setClosed(!door->getClosed());

    if (_on) {
        sprite.setTextureRect(onRect);
    } else {
        sprite.setTextureRect(offRect);
    }
}
