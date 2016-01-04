//
// Created by pawkrol on 12/30/15.
//

#include "Rat.h"
#include "../framework/GameException.h"
#include "../framework/GameWorld.h"
#include "BloodSpot.h"
#include "Explosion.h"

Rat::Rat(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    mobAI = new MobAI(this);

    x_offset = 16;
    y_offset = 16;

    init();
    toIsoCords();
}

void Rat::init() {
    if (!texture.loadFromFile("res/ratWalk.png")){
        throw GameException("Exception: Can't load rat texture");
    }

    goingLeftAnim.setSpriteSheet(texture);
    goingLeftAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(128, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(160, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(192, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(224, 0, 32, 32));

    goingUpAnim.setSpriteSheet(texture);
    goingUpAnim.addFrame(sf::IntRect(0, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(32, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(64, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(96, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(128, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(160, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(192, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(224, 32, 32, 32));

    goingDownAnim.setSpriteSheet(texture);
    goingDownAnim.addFrame(sf::IntRect(0, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(32, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(64, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(96, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(128, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(160, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(192, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(224, 64, 32, 32));

    goingRightAnim.setSpriteSheet(texture);
    goingRightAnim.addFrame(sf::IntRect(0, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(32, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(64, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(96, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(128, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(160, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(192, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(224, 96, 32, 32));

    animation = &goingDownAnim;
    ratWalkSprite = new AnimatedSprite(sf::seconds(.11f));
}

void Rat::update(GameWorld *world) {
    if ( hp <= 0 ){
        die(world);
        return;
    }

    if (!triggered) {
        moveVector = mobAI->getMoveTo(world, deltaTime.asSeconds());
        if (!checkCollision(getObstacles(world))) {
            toCarCords();
            sf::Vector2f oldPos(x, y);
            x = moveVector.x;
            y = moveVector.y;
            setAnimation(oldPos);
            toIsoCords();
        }

        if (checkCollision(world->getPlayer())) {
            triggered = true;
            explosionClock.restart();
        }

        toCarCords();
        float mx = x / (Tile::WIDTH / 2) + 1;
        float my = y / (Tile::HEIGHT / 2) + 1;
        toIsoCords();

        darkness = world->getGroundTileDarkness(mx, my);

        ratWalkSprite->setColor(sf::Color(darkness, darkness, darkness));
    } else {

        ratWalkSprite->setColor(sf::Color(255, 0, 0));
        if (explosionClock.getElapsedTime().asSeconds() > .5) {
            hp = 0;
            die(world);
        }
        return;
    }

    deltaTime = frameClock.restart();
    ratWalkSprite->update(deltaTime);
    ratWalkSprite->setPosition(x, y);
    ratWalkSprite->play(*animation);
}

void Rat::render(sf::RenderWindow *w, Camera *c) {
    if (darkness > 0)
        w->draw(*ratWalkSprite);
}

void Rat::takeDamage(float damage) {
    hp -= damage;
}

void Rat::die(GameWorld *w) {
    toCarCords();
    w->addGroundEntity(new BloodSpot(x, y));
    if (triggered)
        w->addEntity(new Explosion(x, y, true));
    toIsoCords();

    w->removeEntity(this);
}

std::vector<Renderable *> Rat::getObstacles(GameWorld *gc) {
    std::vector<Renderable *> obstacles = gc->getClosestObstacles(this, width);
    std::vector<Renderable *> entities = gc->getClosestEntities(this, width);

    obstacles.insert(obstacles.end(), entities.begin(), entities.end());

    return obstacles;
}

void Rat::setAnimation(sf::Vector2f oldPosition) {
    if (oldPosition.x - x < 0){
        _facing = RIGHT;
        animation = &goingRightAnim;
    } else if (oldPosition.x - x > 0){
        _facing = LEFT;
        animation = &goingLeftAnim;
    } else if (oldPosition.y - y > 0){
        _facing = UP;
        animation = &goingUpAnim;
    } else {
        _facing = DOWN;
        animation = &goingDownAnim;
    }
}

Rat::~Rat() {

}
