//
// Created by pawkrol on 1/8/16.
//

#include "MadPickle.h"
#include "PickleAI.h"
#include "../EffectEntities/PickleShot.h"

MadPickle::MadPickle(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    x_offset = 16;
    y_offset = 16;

    mobAI = new PickleAI(this);

    fullHP = 10.f;
    speed = 10.f;

    _facing = DOWN;
    animation = &goingDownAnim;

    shootTimer.restart();

    toIsoCords();
    init();
}

void MadPickle::init() {
    texture = GameWorld::wrm->getPickleTexture();

    goingDownAnim.setSpriteSheet(*texture);
    goingDownAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(128, 0, 32, 32));

    goingRightAnim.setSpriteSheet(*texture);
    goingRightAnim.addFrame(sf::IntRect(0, 32, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(32, 32, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(64, 32, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(96, 32, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(128, 32, 32, 32));

    goingUpAnim.setSpriteSheet(*texture);
    goingUpAnim.addFrame(sf::IntRect(0, 64, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(32, 64, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(64, 64, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(96, 64, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(128, 64, 32, 32));

    goingLeftAnim.setSpriteSheet(*texture);
    goingLeftAnim.addFrame(sf::IntRect(0, 96, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(32, 96, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(64, 96, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(96, 96, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(128, 96, 32, 32));

    sprite = new AnimatedSprite(sf::seconds(.1f));
    sprite->setAnimation(*animation);
}

void MadPickle::update(GameWorld *world) {
    if (hp <= 0){
        die(world);
        return;
    }

    moveVector = mobAI->getMoveTo(world, frameTime.asSeconds());
    if (!checkCollision(getObstacles(world))) {
        toCarCords();
        sf::Vector2f oldPos(x, y);
        x = moveVector.x;
        y = moveVector.y;
        setAnimation(oldPos);
        toIsoCords();
    }

    toCarCords();
    float mx = x / (Tile::WIDTH / 2) + 1;
    float my = y / (Tile::HEIGHT / 2) + 1;
    toIsoCords();

    darkness = world->getGroundTileDarkness(mx, my);

    sprite->setColor(sf::Color(darkness, darkness, darkness));

    frameTime = frameClock.restart();
    sprite->update(frameTime);
    sprite->setPosition(x, y);
    sprite->play(*animation);
}

void MadPickle::render(sf::RenderWindow *w, Camera *c) {
    if (darkness > 0)
        w->draw(*sprite);
}

void MadPickle::takeDamage(float damage) {
    hp -= damage;
}

void MadPickle::die(GameWorld *world) {
    world->removeEntity(this);
}

void MadPickle::setAnimation(sf::Vector2f oldPosition) {
    if (oldPosition.x - x < 0){
        _facing = RIGHT;
        animation = &goingRightAnim;
    } else if (oldPosition.x - x > 0){
        _facing = LEFT;
        animation = &goingLeftAnim;
    } else if (oldPosition.y - y > 0){
        _facing = UP;
        animation = &goingUpAnim;
    } else if (oldPosition.y - y < 0){
        _facing = DOWN;
        animation = &goingDownAnim;
    }
}

void MadPickle::shootAtPlayer(sf::Vector2f playerPos, GameWorld *world) {
    if (shootTimer.getElapsedTime() > sf::seconds(fireRateSec)) {
        toCarCords();
        world->addEntityQueue(new PickleShot(playerPos.x, playerPos.y));
        toIsoCords();

        shootTimer.restart();
    }
}

std::vector<Renderable *> MadPickle::getObstacles(GameWorld *gc) {
    std::vector<Renderable *> obstacles = gc->getClosestObstacles(this, width);
    std::vector<Renderable *> entities = gc->getClosestEntities(this, width);

    obstacles.insert(obstacles.end(), entities.begin(), entities.end());

    return obstacles;
}

MadPickle::~MadPickle() {
    delete mobAI;
    delete sprite;
}