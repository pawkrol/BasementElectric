//
// Created by pawkrol on 1/2/16.
//

#include "Explosion.h"
#include "../framework/GameException.h"
#include "../framework/GameWorld.h"

Explosion::Explosion(float x, float y, bool givesDamage) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    this->givesDamage = givesDamage;
    this->damageRange = height/2;
    this->collidable = false;

    toIsoCords();

    init();
}

void Explosion::init() {
    if (!texture.loadFromFile("res/explosion.png"))
        throw GameException("Exception: Can't load explosion texture");

    explosionAnim.setSpriteSheet(texture);
    explosionAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(128, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(160, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(192, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(224, 0, 32, 32));

    animation = new AnimatedSprite(sf::seconds(.075f), false, false);

    animation->setPosition(x, y);
    animation->play(explosionAnim);
}

void Explosion::update(GameWorld *world) {
    liveTime = clock.restart();
    animation->update(liveTime);

    if (!animation->isPlaying()){
        die(world);
        return;
    }
}

void Explosion::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*animation);
}

void Explosion::die(GameWorld *world) {
    if (givesDamage){
        Player *p = world->getPlayer();
        double distance = sqrt((x - p->x) * (x - p->x) + (y - p->y) * (y - p->y));
        if (distance <= damageRange) {
            p->takeDamage(10);
        }
    }

    world->removeEntity(this);
}
