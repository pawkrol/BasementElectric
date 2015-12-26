//
// Created by pawkrol on 12/2/15.
//

#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"

Player::Player(float x, float y) {
    this->x = x;
    this->y = y;

    init();
}

void Player::init() {
    if (!texture.loadFromFile("res/playerWalk.png")){
        std::cout << "CAN'T LOAD PLAYER TEXTURE" << std::endl;
    }

    setUpAnimations();
    toIsoCords();
}

void Player::update() {
    frameTime = frameClock.restart();
    animatedSprite->update(frameTime);
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

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}

void Player::movePlayer(Facing direction) { // isMoving = false; if (keypressed) isMoving = true;
    toCarCords();

    if (direction == DOWN){
        animation = &goingDownAnim;
        y += speed;

    } else if (direction == UP){
        animation = &goingUpAnim;
        y -= speed;

    }else if (direction == LEFT){
        animation = &goingLeftAnim;
        x -= speed;

    }else if (direction == RIGHT){
        animation = &goingRightAnim;
        x += speed;
    }

    toIsoCords();
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(x, y);
}

int Player::getViewDistance() {
    return viewDistance;
}