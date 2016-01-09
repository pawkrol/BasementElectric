//
// Created by pawkrol on 1/8/16.
//

#include "PickleShot.h"
#include "../../framework/GameWorld.h"

PickleShot::PickleShot(float x, float y) {
    this->x = x;
    this->y = y;

    width = 32;
    height = 32;

    collidable = false;

    toIsoCords();
    init();
}

void PickleShot::init() {
    texture = GameWorld::wrm->getPickleShotTexture();

    shot.setTexture(*texture);
    shot.setScale(2.f, 2.f);
    shot.setColor(sf::Color(255, 255, 255, 128));
    shot.setPosition(x, y);

    liveClock.restart();
}

void PickleShot::update(GameWorld *world) {
    if (liveClock.getElapsedTime() >= sf::seconds(liveTime) ) {
        Player *player = world->getPlayer();
        double distance = sqrt((player->x - x)*(player->x - x)
                              - (player->y - y) * (player->y - y) );

        if (distance < width/2) {
            player->takeDamage(2.5f);
        }

        die(world);
    }
}

void PickleShot::render(sf::RenderWindow *w, Camera *c) {
    w->draw(shot);
}

void PickleShot::die(GameWorld *world) {
    world->removeEntity(this);
}