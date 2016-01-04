//
// Created by pawkrol on 12/30/15.
//

#include "RatSpawner.h"
#include "../../../framework/GameException.h"
#include "../../../framework/GameWorld.h"
#include "../../Explosion.h"

RatSpawner::RatSpawner(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    isMovable = false;

    hp = 100.f;

    init();
}

RatSpawner::~RatSpawner() { }

void RatSpawner::init() {
    if (!texture.loadFromFile("res/ratSpawner.png")){
        throw GameException("Exception: Can't load player rat spawner");
    }

    animation.setSpriteSheet(texture);
    animation.addFrame(sf::IntRect(0, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));
    animation.addFrame(sf::IntRect(64, 0, 32, 32));
    animation.addFrame(sf::IntRect(96, 0, 32, 32));
    animation.addFrame(sf::IntRect(128, 0, 32, 32));
    animation.addFrame(sf::IntRect(160, 0, 32, 32));
    animation.addFrame(sf::IntRect(192, 0, 32, 32));

    spawnerSprite = new AnimatedSprite(sf::seconds(.2f));

    spawnPoint.x = x;
    spawnPoint.y = y + Tile::HEIGHT/2;
    spawnClock.restart();

    toIsoCords();
}

void RatSpawner::update(GameWorld *world) {
    if ( hp <= 0 ){
        die(world);
        return;
    }

    spawn(world);

    deltaTime = frameClock.restart();
    spawnerSprite->update(deltaTime);
    spawnerSprite->setPosition(x, y);
    spawnerSprite->play(animation);
}

void RatSpawner::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*spawnerSprite);
}

void RatSpawner::spawn(GameWorld *world) {
    if (spawnClock.getElapsedTime().asSeconds() > 6 && spawnedMobs < maxSpawnedMobs){
        spawnClock.restart();
        spawnedMobs++;
        world->addEntity(new Rat(spawnPoint.x, spawnPoint.y, 32, 32));
    }
}

void RatSpawner::takeDamage(float damage) {
    hp -= damage;
}

void RatSpawner::die(GameWorld *w) {
    toCarCords();
    w->addEntity(new Explosion(x, y, false));
    toIsoCords();

    w->removeEntity(this);
}

sf::Vector2f RatSpawner::getSpawnPoint() {
    return spawnPoint;
}