//
// Created by pawkrol on 1/5/16.
//

#include "Doors.h"
#include "../../../framework/GameWorld.h"

Doors::Doors(float x, float y, Side side, bool isClosed, int id) {
    this->x = x;
    this->y = y;
    this->id = id;
    this->isClosed = isClosed;

    x_offset = 12;

    _side = side;

    toIsoCords();
    init();
}

void Doors::init() {
    texture = GameWorld::wrm->getDoorsTexture();

    if (_side == RIGHT || _side == LEFT) {
        anim.setSpriteSheet(*texture);
        anim.addFrame(sf::IntRect(0, 0, 32, 32));
        anim.addFrame(sf::IntRect(32, 0, 32, 32));
        anim.addFrame(sf::IntRect(64, 0, 32, 32));
        anim.addFrame(sf::IntRect(96, 0, 32, 32));
        anim.addFrame(sf::IntRect(128, 0, 32, 32));
        anim.addFrame(sf::IntRect(160, 0, 32, 32));
        anim.addFrame(sf::IntRect(192, 0, 32, 32));

    } else {
        anim.setSpriteSheet(*texture);
        anim.addFrame(sf::IntRect(0, 32, 32, 32));
        anim.addFrame(sf::IntRect(32, 32, 32, 32));
        anim.addFrame(sf::IntRect(64, 32, 32, 32));
        anim.addFrame(sf::IntRect(96, 32, 32, 32));
        anim.addFrame(sf::IntRect(128, 32, 32, 32));
        anim.addFrame(sf::IntRect(160, 32, 32, 32));
        anim.addFrame(sf::IntRect(192, 32, 32, 32));
    }

    sprite = new AnimatedSprite(sf::seconds(.2f), true, false);
    sprite->setAnimation(anim);
    sprite->setPosition(x, y);

    if (!isClosed){
        collidable = false;
        sprite->setFrame(6);
    }
}

void Doors::update() {
    setDarkness(defaultDarkness);

    frameTime = frameClock.restart();
    sprite->update(frameTime);

//    if (!isClosed && !sprite->isPlaying()){
//        sprite->setFrame(6);
//    }
}

void Doors::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*sprite);
}

void Doors::setClosed(bool isClosed) {
    this->isClosed = isClosed;

    if (isClosed){
        collidable = true;
        sprite->setFrame(0);
    } else {
//        sprite->play();
        sprite->setFrame(6);
        collidable = false;
    }
}

bool Doors::getClosed(){
    return isClosed;
}

void Doors::updateDarkness() {
    sprite->setColor(sf::Color(darkness, darkness, darkness));
}

void Doors::setDarkness(sf::Uint8 darkness) {
    this->darkness = darkness;
    updateDarkness();
}

Doors::~Doors() {

}
