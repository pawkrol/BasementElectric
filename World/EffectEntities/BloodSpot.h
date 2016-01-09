//
// Created by pawkrol on 1/1/16.
//

#ifndef DUDESPATROL_BLOODSPOT_H
#define DUDESPATROL_BLOODSPOT_H


#include <SFML/Graphics/VertexArray.hpp>
#include "../../include/GroundEntity.h"

class BloodSpot : public GroundEntity{
private:
    void takeDamage(float damage){};
    void update(){};

    sf::Time liveTime;
    sf::Clock clock;

    sf::VertexArray vertexArray;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void die(GameWorld*);

public:

    BloodSpot(float x, float y);
    void init();
    void update(GameWorld *world);

    void render(sf::RenderWindow *w, Camera *c);
};


#endif //DUDESPATROL_BLOODSPOT_H
