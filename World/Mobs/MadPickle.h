//
// Created by pawkrol on 1/8/16.
//

#ifndef DUDESPATROL_MADPICKLE_H
#define DUDESPATROL_MADPICKLE_H


#include "../../include/Mob.h"
#include "../../framework/sfmlAddon/AnimatedSprite.h"

class PickleAI;

class MadPickle : public Mob {
protected:
    AnimatedSprite *sprite;
    Animation *animation;
    Animation goingDownAnim;
    Animation goingUpAnim;
    Animation goingLeftAnim;
    Animation goingRightAnim;

    sf::Clock frameClock;
    sf::Time frameTime;

    sf::Clock shootTimer;
    float fireRateSec = 3.f;

    sf::Uint8 darkness;

    PickleAI *mobAI;

    void update(){};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const{};

    void die(GameWorld *world);
    void setAnimation(sf::Vector2f oldPosition);
    std::vector<Renderable *> getObstacles(GameWorld *gc);

public:
    MadPickle(float x, float y, float width, float height);
    ~MadPickle();

    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);

    void shootAtPlayer(sf::Vector2f playerPos, GameWorld *world);

    void takeDamage(float damage);
};


#endif //DUDESPATROL_MADPICKLE_H
