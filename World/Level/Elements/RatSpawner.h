//
// Created by pawkrol on 12/30/15.
//

#ifndef DUDESPATROL_RATSPAWNER_H
#define DUDESPATROL_RATSPAWNER_H


#include "../../../include/Entity.h"
#include "../../../framework/sfmlAddon/Animation.h"
#include "../../../framework/sfmlAddon/AnimatedSprite.h"

class RatSpawner : public Entity{
private:
    int maxSpawnedMobs = 0;
    int spawnedMobs = 0;

    sf::Clock spawnClock;

    AnimatedSprite *spawnerSprite;
    Animation animation;

    sf::Clock frameClock;
    sf::Time deltaTime;

    sf::Vector2f spawnPoint;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    void update(){};

    void die(GameWorld*);

public:
    RatSpawner(float x, float y);
    ~RatSpawner();

    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);
    void takeDamage(float damage);
    void spawn(GameWorld *);

    sf::Vector2f getSpawnPoint();
};


#endif //DUDESPATROL_RATSPAWNER_H
