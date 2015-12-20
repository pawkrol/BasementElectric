//
// Created by pawkrol on 12/11/15.
//

#ifndef DUDESPATROL_LIGHTSOURCE_H
#define DUDESPATROL_LIGHTSOURCE_H


#include "../Level.h"

class LightSource {
protected:
    const sf::Uint8 _maxDarkness = 255;
    int distance = 0;
    int distanceMult = 1;

    float x;
    float y;

    int levelWidth;
    int levelHeight;

    Entity *entity;
    Level *level;

    void calcDarkness(Tile *from, Tile *to);
    void setDarknessLevels();

public:
    LightSource();
    LightSource(Level *level);

    void setLightSource(Entity *entity);
    void setLightSource(sf::Vector2f position);
    void setLightSource(float x, float y);

    void setLightDistance(int distance);

    void update();

    sf::Vector2f getPosition();
};

#endif //DUDESPATROL_LIGHTSOURCE_H
