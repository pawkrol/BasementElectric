//
// Created by pawkrol on 12/29/15.
//

#include "PlayerResourceManager.h"
#include "../framework/GameException.h"

void PlayerResourceManager::loadTextures() {
    if (!walkSprites.loadFromFile("res/playerWalk.png")){
        throw GameException("Exception: Can't load player walk sprites");
    }
    if (!idleSprites.loadFromFile("res/playerIdle.png")){
        throw GameException("Exception: Can't load player idle sprites");
    }
    if (!hitSprites.loadFromFile("res/playerHit.png")){
        throw GameException("Exception: Can't load player hit sprites");
    }
}

void PlayerResourceManager::setUpAnimations() {
    goingLeftAnim.setSpriteSheet(walkSprites);
    goingLeftAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(128, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(160, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(192, 0, 32, 32));
    goingLeftAnim.addFrame(sf::IntRect(224, 0, 32, 32));

    goingUpAnim.setSpriteSheet(walkSprites);
    goingUpAnim.addFrame(sf::IntRect(0, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(32, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(64, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(96, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(128, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(160, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(192, 32, 32, 32));
    goingUpAnim.addFrame(sf::IntRect(224, 32, 32, 32));

    goingDownAnim.setSpriteSheet(walkSprites);
    goingDownAnim.addFrame(sf::IntRect(0, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(32, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(64, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(96, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(128, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(160, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(192, 64, 32, 32));
    goingDownAnim.addFrame(sf::IntRect(224, 64, 32, 32));

    goingRightAnim.setSpriteSheet(walkSprites);
    goingRightAnim.addFrame(sf::IntRect(0, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(32, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(64, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(96, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(128, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(160, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(192, 96, 32, 32));
    goingRightAnim.addFrame(sf::IntRect(224, 96, 32, 32));

    idleUpAnim.setSpriteSheet(idleSprites);
    idleUpAnim.addFrame(sf::IntRect(0, 0, 32, 32));

    idleLeftAnim.setSpriteSheet(idleSprites);
    idleLeftAnim.addFrame(sf::IntRect(32, 0, 32, 32));

    idleRightAnim.setSpriteSheet(idleSprites);
    idleRightAnim.addFrame(sf::IntRect(64, 0, 32, 32));

    idleDownAnim.setSpriteSheet(idleSprites);
    idleDownAnim.addFrame(sf::IntRect(96, 0, 32, 32));

    hitUpAnim.setSpriteSheet(hitSprites);
    hitUpAnim.addFrame(sf::IntRect(0, 0, 32, 32));
    hitUpAnim.addFrame(sf::IntRect(0, 32, 32, 32));
    hitUpAnim.addFrame(sf::IntRect(0, 64, 32, 32));
    hitUpAnim.addFrame(sf::IntRect(0, 96, 32, 32));
    hitUpAnim.addFrame(sf::IntRect(0, 128, 32, 32));

    hitLeftAnim.setSpriteSheet(hitSprites);
    hitLeftAnim.addFrame(sf::IntRect(32, 0, 32, 32));
    hitLeftAnim.addFrame(sf::IntRect(32, 32, 32, 32));
    hitLeftAnim.addFrame(sf::IntRect(32, 64, 32, 32));
    hitLeftAnim.addFrame(sf::IntRect(32, 96, 32, 32));
    hitLeftAnim.addFrame(sf::IntRect(32, 128, 32, 32));

    hitRightAnim.setSpriteSheet(hitSprites);
    hitRightAnim.addFrame(sf::IntRect(64, 0, 32, 32));
    hitRightAnim.addFrame(sf::IntRect(64, 32, 32, 32));
    hitRightAnim.addFrame(sf::IntRect(64, 64, 32, 32));
    hitRightAnim.addFrame(sf::IntRect(64, 96, 32, 32));
    hitRightAnim.addFrame(sf::IntRect(64, 128, 32, 32));

    hitDownAnim.setSpriteSheet(hitSprites);
    hitDownAnim.addFrame(sf::IntRect(96, 0, 32, 32));
    hitDownAnim.addFrame(sf::IntRect(96, 32, 32, 32));
    hitDownAnim.addFrame(sf::IntRect(96, 64, 32, 32));
    hitDownAnim.addFrame(sf::IntRect(96, 96, 32, 32));
    hitDownAnim.addFrame(sf::IntRect(96, 128, 32, 32));
}

Animation* PlayerResourceManager::getAnimation(ANIM anim) {
    switch (anim){
        case WALK_UP:
            return &goingUpAnim;

        case WALK_DOWN:
            return &goingDownAnim;

        case WALK_LEFT:
            return &goingLeftAnim;

        case WALK_RIGHT:
            return &goingRightAnim;

        case IDLE_UP:
            return &idleUpAnim;

        case IDLE_DOWN:
            return &idleDownAnim;

        case IDLE_RIGHT:
            return &idleRightAnim;

        case IDLE_LEFT:
            return &idleLeftAnim;

        case HIT_UP:
            return &hitUpAnim;

        case HIT_DOWN:
            return &hitDownAnim;

        case HIT_RIGHT:
            return &hitRightAnim;

        case HIT_LEFT:
            return &hitLeftAnim;
    }
}