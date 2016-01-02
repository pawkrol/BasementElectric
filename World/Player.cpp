//
// Created by pawkrol on 12/2/15.
//

#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "../framework/GameWorld.h"

Player::Player(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    moveVector.x = x;
    moveVector.y = y;

    _facing = DOWN;
    _state = IDLE;

    init();
}

void Player::init() {
    prm.loadTextures();

    setUpAnimations();
    toIsoCords();
}

void Player::update(GameWorld *world) {
    deltaTime = frameClock.restart();

    if (!checkCollision(getObstacles(world)))
        updateIsoPosition(moveVector);

    updateAnimation();
    manageState(world);
}

std::vector<Renderable *> Player::getObstacles(GameWorld *gc) {
    std::vector<Renderable *> obstacles = gc->getClosestObstacles(this);
    std::vector<Renderable *> entities = gc->getClosestEntities(this, width);

    obstacles.insert(obstacles.end(), entities.begin(), entities.end());

    return obstacles;
}

void Player::manageState(GameWorld *g) {
    switch (_state){
        case IDLE:
            if (_facing == DOWN)
                idleAnimation = prm.getAnimation(prm.IDLE_DOWN);
            else if (_facing == UP)
                idleAnimation = prm.getAnimation(prm.IDLE_UP);
            else if (_facing == LEFT)
                idleAnimation = prm.getAnimation(prm.IDLE_LEFT);
            else if (_facing == RIGHT)
                idleAnimation = prm.getAnimation(prm.IDLE_RIGHT);

            animatedSprite->play(*idleAnimation);

            _state = IDLE;

            break;

        case WALK:
            movePlayer();
            _state = IDLE;

            break;

        case HIT:
            if (!animatedSprite->isPlaying())
                _state = IDLE;

            for (Renderable *e : g->getClosestEntities(this, width*4/3)){
                Entity *entity = (Entity *)e;

                if (((entity->_facing == DOWN && _facing == UP) ||
                        (entity->_facing == UP && _facing == DOWN) ||
                        (entity->_facing == LEFT && _facing == RIGHT) ||
                        (entity->_facing == RIGHT && _facing == LEFT)) && isMovable) {

                    entity->takeDamage(2);

                } else {
                    if (checkCollision(e))
                        entity->takeDamage(1);
                }
            }

            break;
    }
}

void Player::updateAnimation() {
    animatedSprite->update(deltaTime);
    animatedSprite->setPosition(x, y);
}

void Player::setUpAnimations() {
    prm.setUpAnimations();
    animatedSprite = new AnimatedSprite(sf::seconds(0.12f), true, false);
}

void Player::render(sf::RenderWindow *w, Camera *c) {
   if (hp > 0)
        w->draw(*animatedSprite);
}

void Player::movePlayer() {
    toCarCords();

    moveVector.x = x;
    moveVector.y = y;

    if (_facing == DOWN){
        walkAnimation = prm.getAnimation(prm.WALK_DOWN);
        moveVector.y = y + speed * deltaTime.asSeconds();

    } else if (_facing == UP){
        walkAnimation = prm.getAnimation(prm.WALK_UP);
        moveVector.y = y - speed * deltaTime.asSeconds();

    } else if (_facing == LEFT){
        walkAnimation = prm.getAnimation(prm.WALK_LEFT);
        moveVector.x = x - speed * deltaTime.asSeconds();

    } else if (_facing == RIGHT){
        walkAnimation = prm.getAnimation(prm.WALK_RIGHT);
        moveVector.x = x + speed * deltaTime.asSeconds();
    }

    toIsoCords();

    animatedSprite->setFrameTime(sf::seconds(.12f));
    animatedSprite->play(*walkAnimation);
}

void Player::move(Facing direction) {
    _facing = direction;
    _state = WALK;
}

void Player::hitEnemyAnimation() {
    if (_facing == DOWN)
        hitAnimation = prm.getAnimation(prm.HIT_DOWN);
    else if (_facing == UP)
        hitAnimation = prm.getAnimation(prm.HIT_UP);
    else if (_facing == LEFT)
        hitAnimation = prm.getAnimation(prm.HIT_LEFT);
    else if (_facing == RIGHT)
        hitAnimation = prm.getAnimation(prm.HIT_RIGHT);

    animatedSprite->setFrameTime(sf::seconds(.04f));
    animatedSprite->play(*hitAnimation);
}

void Player::hit() { //implement stamina if <= 0 -> cannot hit
    hitEnemyAnimation();
    _state = HIT;
}

void Player::takeDamage(float damage) {
    hp -= damage;
}

void Player::die(GameWorld *w) {

}

void Player::updateIsoPosition(sf::Vector2f pos) {
    toCarCords();
        x = pos.x;
        y = pos.y;
    toIsoCords();
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(x, y);
}

int Player::getViewDistance() {
    return viewDistance;
}