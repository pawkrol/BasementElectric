//
// Created by pawkrol on 12/30/15.
//

#ifndef DUDESPATROL_RAT_H
#define DUDESPATROL_RAT_H

#include "../include/Entity.h"
#include "../framework/sfmlAddon/Animation.h"
#include "../framework/sfmlAddon/AnimatedSprite.h"
#include "MobAI.h"

class Rat : public Entity{
private:
    bool triggered = false;

    AnimatedSprite *ratWalkSprite;
    Animation *animation;
    Animation goingUpAnim;
    Animation goingDownAnim;
    Animation goingLeftAnim;
    Animation goingRightAnim;

    MobAI *mobAI;

    sf::Clock explosionClock;
    sf::Clock frameClock;
    sf::Time deltaTime;

    sf::Uint8 darkness;

    void update(){};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};

    std::vector<Renderable *> getObstacles(GameWorld*);
    void setAnimation(sf::Vector2f oldPosition);

    void die(GameWorld*);

public:
    Rat(float x, float y, float width, float height);
    ~Rat();

    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);

    void takeDamage(float damage);
};


#endif //DUDESPATROL_RAT_H
