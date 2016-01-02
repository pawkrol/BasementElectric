//
// Created by pawkrol on 12/2/15.
//

#ifndef DUDESPATROL_PLAYER_H
#define DUDESPATROL_PLAYER_H


#include <SFML/Graphics/VertexArray.hpp>

#include "../include/Entity.h"
#include "../framework/sfmlAddon/AnimatedSprite.h"
#include "PlayerResourceManager.h"

class Player : public Entity{
private:
    PlayerResourceManager prm;

    const int viewDistance = 128;
    float speed = 34.f;

    enum States{
        IDLE, WALK, HIT
    };
    States _state;

    sf::Clock frameClock;
    sf::Time deltaTime;

    AnimatedSprite *animatedSprite;
    Animation *walkAnimation;
    Animation *idleAnimation;
    Animation *hitAnimation;

    std::vector<Renderable *> getObstacles(GameWorld *);

    void updateIsoPosition(sf::Vector2f pos);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    void update(){};

    void setUpAnimations();
    void updateAnimation();
    void manageState(GameWorld*);
    void die(GameWorld*);

    void movePlayer();
    void hitEnemyAnimation();

public:
    Player(float x, float y, float width, float height);

    void init();
    void update(GameWorld *);
    void render(sf::RenderWindow *w, Camera *c);

    void hit();
    void move(Facing direction);

    void takeDamage(float damage);

    sf::Vector2f getPosition();

    int getViewDistance();
};


#endif //DUDESPATROL_PLAYER_H
