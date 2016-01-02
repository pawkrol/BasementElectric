//
// Created by pawkrol on 1/1/16.
//

#include "BloodSpot.h"
#include "../framework/GameException.h"
#include "Level/Elements/Tile.h"
#include "../framework/GameWorld.h"

BloodSpot::BloodSpot(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    this->collidable = false;

    toIsoCords();
    setPosition(x, y);

    init();

    clock.restart();
}

void BloodSpot::init() {
    if (!texture.loadFromFile("res/bloodSpot.png"))
        throw GameException("Exception: Can't load bloodSpot texture");

    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(4);

    vertexArray[0].position = sf::Vector2f(x, y);
    vertexArray[1].position = sf::Vector2f((x + width), y);
    vertexArray[2].position = sf::Vector2f((x + width), (y + height));
    vertexArray[3].position = sf::Vector2f(x, (y + height));

    vertexArray[0].texCoords = sf::Vector2f(0, 0);
    vertexArray[1].texCoords = sf::Vector2f(width, 0);
    vertexArray[2].texCoords = sf::Vector2f(width, height);
    vertexArray[3].texCoords = sf::Vector2f(0, height);

}

void BloodSpot::update(GameWorld *world) {
    liveTime = clock.getElapsedTime();
    if (liveTime.asSeconds() > 5) {
        die(world);
        return;
    }

    toCarCords();
    float mx = x / (Tile::WIDTH/2);
    float my = y / (Tile::HEIGHT/2);
    toIsoCords();

    sf::Uint8 darkness = world->getGroundTileDarkness(mx, my);
    sf::Uint8 opacity = sf::Uint8(255 - liveTime.asSeconds() * 50);

    vertexArray[0].color = sf::Color(darkness, darkness, darkness, opacity);
    vertexArray[1].color = sf::Color(darkness, darkness, darkness, opacity);
    vertexArray[2].color = sf::Color(darkness, darkness, darkness, opacity);
    vertexArray[3].color = sf::Color(darkness, darkness, darkness, opacity);
}

void BloodSpot::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*this);
}

void BloodSpot::die(GameWorld *w) {
    w->removeGroundEntity(this);
}

void BloodSpot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &texture;
    target.draw(vertexArray, states);
}
