//
// Created by pawkrol on 12/29/15.
//

#ifndef DUDESPATROL_PLAYERRESOURCEMANAGER_H
#define DUDESPATROL_PLAYERRESOURCEMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include "../framework/sfmlAddon/Animation.h"

class PlayerResourceManager {
private:
    sf::Texture walkSprites;
    sf::Texture idleSprites;
    sf::Texture hitSprites;

    Animation goingUpAnim;
    Animation goingDownAnim;
    Animation goingLeftAnim;
    Animation goingRightAnim;

    Animation idleUpAnim;
    Animation idleDownAnim;
    Animation idleLeftAnim;
    Animation idleRightAnim;

    Animation hitUpAnim;
    Animation hitDownAnim;
    Animation hitLeftAnim;
    Animation hitRightAnim;

public:
    enum ANIM{
        WALK_UP,
        WALK_DOWN,
        WALK_LEFT,
        WALK_RIGHT,

        IDLE_UP,
        IDLE_DOWN,
        IDLE_RIGHT,
        IDLE_LEFT,

        HIT_UP,
        HIT_DOWN,
        HIT_RIGHT,
        HIT_LEFT
    };

    void loadTextures();

    void setUpAnimations();

    Animation* getAnimation(ANIM anim);
};


#endif //DUDESPATROL_PLAYERRESOURCEMANAGER_H
