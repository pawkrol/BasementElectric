//
// Created by pawkrol on 1/5/16.
//

#include "Doors.h"
#include "../../../framework/GameException.h"

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
    if (!texture.loadFromFile("res/door.png")){
        throw GameException("Exception: Can't load door texture");
    }

    animation.setSpriteSheet(texture);
    animation.addFrame(sf::IntRect(0, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));
    animation.addFrame(sf::IntRect(64, 0, 32, 32));
    animation.addFrame(sf::IntRect(96, 0, 32, 32));
    animation.addFrame(sf::IntRect(128, 0, 32, 32));
    animation.addFrame(sf::IntRect(160, 0, 32, 32));
    animation.addFrame(sf::IntRect(192, 0, 32, 32));

    sprite = new AnimatedSprite(sf::seconds(.2f), true, false);
    sprite->setAnimation(animation);
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
//        collidable = false;
//    }
}

void Doors::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*sprite);
}

void Doors::setClosed(bool isClosed) {
    this->isClosed = isClosed;

    if (isClosed){
        collidable = true;
//        sprite->play();
        sprite->setFrame(0);
    } else {
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
