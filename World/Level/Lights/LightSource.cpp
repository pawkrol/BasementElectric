//
// Created by pawkrol on 12/11/15.
//

#include "LightSource.h"

LightSource::LightSource() : entity(NULL), level(NULL) {
    this->x = 0;
    this->y = 0;
    this->levelWidth = 0;
    this->levelHeight = 0;
}
LightSource::LightSource(Level *level) : entity(NULL){
    this->x = 0;
    this->y = 0;
    this->level = level;

    this->levelWidth = level->getSize().x;
    this->levelHeight = level->getSize().y;
}

void LightSource::setLightSource(Entity *entity) {
    entity->toCarCords();
    this->x = entity->x / 16;
    this->y = entity->y / 16;
    entity->toIsoCords();

    this->entity = entity;
}

void LightSource::setLightSource(sf::Vector2f position) {
    this->x = position.x;
    this->y = position.y;
}

void LightSource::setLightSource(float x, float y) {
    this->x = x;
    this->y = y;
}

void LightSource::setLightDistance(int distance) {
    this->distance = distance;
    distanceMult = 256 / distance;
}

void LightSource::update() {
    if (entity != NULL) {
        entity->toCarCords();
        this->x = (entity->x / 16) + 1;
        this->y = (entity->y / 16) + 1;
        entity->toIsoCords();
    }

    setDarknessLevels();
}

sf::Vector2f LightSource::getPosition() {
    return sf::Vector2<float>(x, y);
}

void LightSource::setDarknessLevels() {
    Tile *from;
    Tile *to;

    for (int y = 0; y < levelHeight; ++y ){
        for (int x = 0; x < levelWidth; ++x ){
            if ((from = (*level)(0, x + y * levelWidth)) != NULL) {
                from->update();
                to = level->getTile((int)this->x, (int)this->y);
                if (to != NULL)
                    calcDarkness(from, to);
            }
            if ((from = (*level)(1, x + y * levelWidth)) != NULL) {
                from->update();
                to = level->getTile((int)this->x, (int)this->y);
                if (to != NULL)
                    calcDarkness(from, to);
            }
        }
    }
}


void LightSource::calcDarkness(Tile* from, Tile *to) {
    int distance = int(sqrt((to->x - from->x)*(to->x - from->x)
                        + (to->y - from->y)*(to->y - from->y)));

    if (distance > -1 && distance < this->distance)
        from->setDarkness(sf::Uint8( _maxDarkness - distanceMult*distance ));
}
