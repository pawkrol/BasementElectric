//
// Created by pawkrol on 1/2/16.
//

#ifndef DUDESPATROL_EXPLOSION_H
#define DUDESPATROL_EXPLOSION_H

#include "../include/Entity.h"
#include "../framework/sfmlAddon/Animation.h"
#include "../framework/sfmlAddon/AnimatedSprite.h"

class Explosion : public Entity{
private:
    bool givesDamage;
    float damageRange;

    void takeDamage(float damage){};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const{};
    void update(){};

    AnimatedSprite *animation;
    Animation explosionAnim;

    sf::Time liveTime;
    sf::Clock clock;

    void die(GameWorld*);

public:

    Explosion(float x, float y, bool givesDamage);
    void init();
    void update(GameWorld *world);

    void render(sf::RenderWindow *w, Camera *c);
};


#endif //DUDESPATROL_EXPLOSION_H
