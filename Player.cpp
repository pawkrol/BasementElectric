//
// Created by pawkrol on 12/2/15.
//

#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "framework/GameException.h"

Player::Player(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    moveVector.x = x;
    moveVector.y = y;

    init();
}

void Player::init() {
    if (!texture.loadFromFile("res/playerWalk.png")){
        throw GameException("Exception: Can't load player texture");
    }

    setUpAnimations();
    toIsoCords();
}

void Player::update(std::vector<Renderable *> obstacles) {
    deltaTime = frameClock.restart();

    if (!checkCollision(obstacles))
        updateIsoPosition(moveVector);

    animatedSprite->update(deltaTime);
    animatedSprite->setPosition(x, y);
    animatedSprite->play(*animation);
}

void Player::setUpAnimations() {
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
    animatedSprite = new AnimatedSprite(sf::seconds(0.12), true, false);
}

void Player::render(sf::RenderWindow *w, Camera *c) {
    w->draw(*animatedSprite);
}

void Player::movePlayer(Facing direction) {
    toCarCords();

    moveVector.x = x;
    moveVector.y = y;

    if (direction == DOWN){
        animation = &goingDownAnim;
        moveVector.y = y + speed * deltaTime.asSeconds();

    } else if (direction == UP){
        animation = &goingUpAnim;
        moveVector.y = y - speed * deltaTime.asSeconds();

    } else if (direction == LEFT){
        animation = &goingLeftAnim;
        moveVector.x = x - speed * deltaTime.asSeconds();

    } else if (direction == RIGHT){
        animation = &goingRightAnim;
        moveVector.x = x + speed * deltaTime.asSeconds();
    }

    toIsoCords();
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