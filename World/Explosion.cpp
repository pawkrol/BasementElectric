//
// Created by pawkrol on 1/2/16.
//

#include "Explosion.h"
#include "../framework/GameWorld.h"

Explosion::Explosion(float x, float y, bool givesDamage) {
    this->x = x;
    this->y = y;
    this->width = 32;
    this->height = 32;

    this->givesDamage = givesDamage;
    this->damageRange = height*4/3;
    this->collidable = false;

    toIsoCords();

    init();
}

void Explosion::init() {
    texture = GameWorld::wrm->getExplosionTexture();

    explosionAnim.setSpriteSheet(*texture);
    explosionAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(128, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(160, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(192, 0, 32, 32));
    explosionAnim.addFrame(sf::IntRect(224, 0, 32, 32));

    animation = new AnimatedSprite(sf::seconds(.09f), false, false);

    animation->setPosition(x, y);
    animation->play(explosionAnim);
}

void Explosion::update(GameWorld *world) {
    liveTime = clock.restart();
    animation->update(liveTime);

    if (animation->getCurrentFrameId() == 2){
        if (givesDamage){
            for (Renderable *p : world->getClosestEntities(this, damageRange)) {
                ((Entity*)p)->takeDamage(10);
            }
            givesDamage = false;
        }
    }

    if (!animation->isPlaying()){
        die(world);
        return;
    }
}

void Explosion::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*animation);
    c->shake();
}

void Explosion::die(GameWorld *world) {
    world->removeEntity(this);
}
