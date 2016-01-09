//
// Created by pawkrol on 1/8/16.
//

#ifndef DUDESPATROL_AOEATTACK_H
#define DUDESPATROL_AOEATTACK_H


#include "../../include/Entity.h"
#include "../../framework/sfmlAddon/AnimatedSprite.h"

class AOEattack : public Entity{
private:
    float const _damageRange = 48;

    std::vector<sf::Vector2f> positions;

    AnimatedSprite *sprite;
    Animation animation;

    sf::Clock timer;
    sf::Time frameTime;

    void getPositionsFromTiles(std::vector<Renderable *> tiles);

protected:
    void update(){};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    void takeDamage(float damage){};

    void die(GameWorld *world);

public:

    AOEattack(float x, float y);
    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);
};


#endif //DUDESPATROL_AOEATTACK_H
