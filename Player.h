//
// Created by pawkrol on 12/2/15.
//

#ifndef DUDESPATROL_PLAYER_H
#define DUDESPATROL_PLAYER_H


#include <SFML/Graphics/VertexArray.hpp>
#include "include/Entity.h"
#include "framework/sfmlAddon/AnimatedSprite.h"

class Player : public Entity{
private:
    const int viewDistance = 128;

    sf::Clock frameClock;
    sf::Time frameTime;

    AnimatedSprite *animatedSprite;
    Animation *animation;
    Animation goingUpAnim;
    Animation goingDownAnim;
    Animation goingLeftAnim;
    Animation goingRightAnim;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setUpAnimations();

public:
    static const int WIDTH = 32;
    static const int HEIGHT = 32;

    enum Facing{
        UP, DOWN, LEFT, RIGHT
    };

    Player(float x, float y);

    void init();
    void update();
    void render(sf::RenderWindow *w, Camera *c);
    void movePlayer(Facing direction);

    sf::Vector2f getPosition();

    int getViewDistance();
};


#endif //DUDESPATROL_PLAYER_H
