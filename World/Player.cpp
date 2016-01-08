//
// Created by pawkrol on 12/2/15.
//

#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "../framework/GameWorld.h"
#include "../include/ActionObject.h"
#include "AOEattack.h"

Player::Player(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    moveVector.x = x;
    moveVector.y = y;

    _facing = UP;
    _state = IDLE;

    init();
}

void Player::init() {
    prm.loadTextures();

    hitTicker.restart();

    setUpAnimations();
    toIsoCords();
}

void Player::update(GameWorld *world) {
    if (hp <= 0){
        die(world);
        return;
    }

    deltaTime = frameClock.restart();

    if (_state != HIT &&
            staminaTicker.getElapsedTime().asSeconds() > 10.f){
        setStamina(Player::stamina + 5.f);
        staminaTicker.restart();
    }

    if (!checkCollision(world))
        updateIsoPosition(moveVector);

    updateAnimation();
    manageState(world);
}

std::vector<Renderable *> Player::getObstacles(GameWorld *gc) {
    std::vector<Renderable *> obstacles = gc->getClosestObstacles(this, width);
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
            if (animatedSprite->getAnimation() == hitAnimation &&
                    !animatedSprite->isPlaying()) {
                _state = IDLE;
            }

            for (Renderable *e : g->getClosestEntities(this, width*2/3)){
                Entity *entity = (Entity *)e;

                if (((entity->_facing == DOWN && _facing == UP) ||
                        (entity->_facing == UP && _facing == DOWN) ||
                        (entity->_facing == LEFT && _facing == RIGHT) ||
                        (entity->_facing == RIGHT && _facing == LEFT)) && entity->isMovable) {

                    entity->takeDamage(2);

                } else {
                    if (Entity::checkCollision(e))
                        entity->takeDamage(1);
                }
            }

            if (hitTicker.getElapsedTime().asSeconds() > .5f) {
                setStamina(Player::stamina - 5.f);
                hitTicker.restart();
            }

            break;

        case AOEHIT:
            if (animatedSprite->getAnimation() == hitAnimation &&
                !animatedSprite->isPlaying()) {
                _state = IDLE;

                toCarCords();
                g->addEntityQueue(new AOEattack(x, y));
                toIsoCords();

                setStamina(Player::stamina - 20.f);
            }

            break;

        case ACTION:
            if (animatedSprite->getAnimation() == hitAnimation &&
                    !animatedSprite->isPlaying()) {
                _state = IDLE;

                for (Renderable *r : g->getClosestActionObjects(this, width)) {
                    if (Entity::checkCollision(r)) {
                        ((ActionObject *) r)->action();
                    }
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

void Player::hit() {
    if (_state != HIT && stamina > 0) {
        hitEnemyAnimation();
        _state = HIT;
    }
}

void Player::aoeHit() {
    if (_state != AOEHIT && stamina >= 20.f){
        hitEnemyAnimation();
        _state = AOEHIT;
    }
}

void Player::action() {
    if (_state != ACTION){
        hitEnemyAnimation();
        _state = ACTION;
    }
}

void Player::takeDamage(float damage) {
    hp -= damage;
}

void Player::die(GameWorld *w) {
    w->removeEntity(this);
}

bool Player::checkCollision(GameWorld *g) {
    for (Renderable *o: getObstacles(g)){
        if (!o->collidable) continue;

        if (Entity::checkCollision(o)) {
            if (o->collectable){
                collect(g, o);
                continue;
            }
            return true;
        }
    }

    return false;
}

void Player::collect(GameWorld *g, Renderable *r) {
    r->manageCollectableFor(g, this);
}

void Player::updateIsoPosition(sf::Vector2f pos) {
    toCarCords();
        x = pos.x;
        y = pos.y;
    toIsoCords();
}

float Player::getStamina(){
    return Player::stamina;
}

void Player::setStamina(float stamina){
    if (stamina > Player::fullStamina){
        Player::stamina = Player::fullStamina;
    } else if (stamina < 0 ){
        Player::stamina = 0;
    } else {
        Player::stamina = stamina;
    }
}

float Player::getFullStamina(){
    return Player::fullStamina;
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(x, y);
}

int Player::getViewDistance() {
    return viewDistance;
}
