//
// Created by pawkrol on 1/4/16.
//

#ifndef DUDESPATROL_COLLECTABLESTAMINA_H
#define DUDESPATROL_COLLECTABLESTAMINA_H


#include "../include/Renderable.h"
#include "../framework/sfmlAddon/AnimatedSprite.h"

class CollectableStamina : public Renderable{
private:
    AnimatedSprite *animatedSprite;
    Animation animation;

    sf::Clock frameClock;
    sf::Time frameTime;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};

public:
    CollectableStamina(float x, float y);

    void init();
    void update();
    void render(sf::RenderWindow *w, Camera *c);
    void manageCollectableFor(GameWorld *gw, Entity *entity);

};


#endif //DUDESPATROL_COLLECTABLESTAMINA_H
