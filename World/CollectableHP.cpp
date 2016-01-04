//
// Created by pawkrol on 1/4/16.
//

#include "CollectableHP.h"
#include "../framework/GameException.h"
#include "../framework/GameWorld.h"

CollectableHP::CollectableHP(float x, float y) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    collectable = true;

    init();
    toIsoCords();
}

void CollectableHP::init() {
    if (!texture.loadFromFile("res/collectTomato.png")){
        throw GameException("Exception: Can't load hp collectable");
    }

    animation.setSpriteSheet(texture);
    animation.addFrame(sf::IntRect(0, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));
    animation.addFrame(sf::IntRect(64, 0, 32, 32));
    animation.addFrame(sf::IntRect(96, 0, 32, 32));
    animation.addFrame(sf::IntRect(128, 0, 32, 32));
    animation.addFrame(sf::IntRect(96, 0, 32, 32));
    animation.addFrame(sf::IntRect(64, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));

    animatedSprite = new AnimatedSprite(sf::seconds(.4f));
}

void CollectableHP::update() {
    frameTime = frameClock.restart();
    animatedSprite->update(frameTime);
    animatedSprite->setPosition(x, y);
    animatedSprite->play(animation);
}

void CollectableHP::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*animatedSprite);
}

void CollectableHP::manageCollectableFor(GameWorld *gW, Entity *entity) {
    if (gW->getLevelEffects() != nullptr ){
        gW->getLevelEffects()->buffGain(sf::Color(255, 30, 30));
    }
    entity->setHP(entity->getHP() + 5.f);
    gW->removeObstacle(this);
}