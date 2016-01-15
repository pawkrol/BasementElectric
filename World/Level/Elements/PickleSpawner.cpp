//
// Created by pawkrol on 1/12/16.
//

#include "PickleSpawner.h"
#include "Tile.h"
#include "../../../framework/GameWorld.h"
#include "../../EffectEntities/Explosion.h"
#include "../../Mobs/MadPickle.h"


PickleSpawner::PickleSpawner(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    isMovable = false;

    hp = 100.f;

    init();
}

void PickleSpawner::init() {
    texture = GameWorld::wrm->getPickleSpawnerTexture();

    animation.setSpriteSheet(*texture);
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

void PickleSpawner::update(GameWorld *world) {
    if ( hp <= 0 ){
        die(world);
        return;
    }

    spawn(world);

    deltaTime = frameClock.restart();
    spawnerSprite->update(deltaTime);
    sf::Uint8 dark = sf::Uint8(hp * 2 + 55);
    spawnerSprite->setColor(sf::Color(dark, dark, dark));
    spawnerSprite->setPosition(x, y);
    spawnerSprite->play(animation);
}

void PickleSpawner::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*spawnerSprite);
}

void PickleSpawner::die(GameWorld *world) {
    toCarCords();
    world->addEntity(new Explosion(x, y, false));
    toIsoCords();

    world->removeEntity(this);
}

void PickleSpawner::takeDamage(float damage) {
    hp -= damage;
}

void PickleSpawner::spawn(GameWorld *world) {
    if (spawnClock.getElapsedTime().asSeconds() > 6 && spawnedMobs < maxSpawnedMobs){
        spawnClock.restart();
        spawnedMobs++;
        world->addEntityQueue(new MadPickle(spawnPoint.x, spawnPoint.y, 32, 32));
    }
}

PickleSpawner::~PickleSpawner() { }