//
// Created by pawkrol on 1/8/16.
//

#include "AOEattack.h"
#include "../../framework/GameWorld.h"

AOEattack::AOEattack(float x, float y) {
    this->x = x;
    this->y = y;

    collidable = false;

    toIsoCords();
    init();
}

void AOEattack::getPositionsFromTiles(std::vector<Renderable *> tiles) {
    for (Renderable *t : tiles){
        positions.push_back(sf::Vector2f(t->x, t->y));
    }
}

void AOEattack::init() {
    texture = GameWorld::wrm->getAOETexture();

    animation.setSpriteSheet(*texture);
    animation.addFrame(sf::IntRect(0, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));
    animation.addFrame(sf::IntRect(64, 0, 32, 32));
    animation.addFrame(sf::IntRect(96, 0, 32, 32));
    animation.addFrame(sf::IntRect(128, 0, 32, 32));
    animation.addFrame(sf::IntRect(160, 0, 32, 32));
    animation.addFrame(sf::IntRect(192, 0, 32, 32));
    animation.addFrame(sf::IntRect(224, 0, 32, 32));

    sprite = new AnimatedSprite(sf::seconds(.09f), false, false);

    sprite->play(animation);
}

void AOEattack::update(GameWorld *world) {
    frameTime = timer.restart();
    sprite->update(frameTime);

    if (!sprite->isPlaying()){
        die(world);
        return;
    }

    if (sprite->getCurrentFrameId() == 1){
            for (Renderable *p : world->getClosestEntities(this, _damageRange)) {
                if (((Entity *) p)->isMovable && p != world->getPlayer()) {
                    ((Entity *) p)->takeDamage(20);
                }
            }
    }

    toCarCords();
    getPositionsFromTiles(world->getClosestGroundTiles(sf::Vector2f(x, y)));
    toIsoCords();

}

void AOEattack::render(sf::RenderWindow *w, Camera *c) {
    c->shake();
    for (sf::Vector2f pos : positions) {
        sprite->setPosition(pos);
        w->draw(*sprite);
    }
}

void AOEattack::die(GameWorld *world) {
    world->removeEntity(this);
}
