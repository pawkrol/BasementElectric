//
// Created by pawkrol on 1/12/16.
//

#ifndef DUDESPATROL_PICKLESPAWNER_H
#define DUDESPATROL_PICKLESPAWNER_H


#include "../../../include/Entity.h"
#include "../../../framework/sfmlAddon/Animation.h"
#include "../../../framework/sfmlAddon/AnimatedSprite.h"

class PickleSpawner : public Entity {
private:
    int maxSpawnedMobs = 2;
    int spawnedMobs = 0;

    sf::Clock spawnClock;

    AnimatedSprite *spawnerSprite;
    Animation animation;

    sf::Clock frameClock;
    sf::Time deltaTime;

    sf::Vector2f spawnPoint;

    void update(){};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};

    void die(GameWorld *world);

public:

    PickleSpawner(float x, float y);
    ~PickleSpawner();

    void init();
    void update(GameWorld *world);
    void render(sf::RenderWindow *w, Camera *c);

    void spawn(GameWorld *);
    void takeDamage(float damage);
};


#endif //DUDESPATROL_PICKLESPAWNER_H
