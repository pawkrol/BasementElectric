//
// Created by pawkrol on 1/8/16.
//

#ifndef DUDESPATROL_PICKLESHOT_H
#define DUDESPATROL_PICKLESHOT_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../include/Entity.h"

class PickleShot : public Entity{
private:
    sf::Sprite shot;
    sf::Clock liveClock;
    float liveTime = 1.f;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const{};
    void takeDamage(float damage){};
    void update(){};

    void die(GameWorld *world);

public:
    PickleShot(float x, float y);

    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);
};


#endif //DUDESPATROL_PICKLESHOT_H
