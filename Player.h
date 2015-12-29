//
// Created by pawkrol on 12/2/15.
//

#ifndef DUDESPATROL_PLAYER_H
#define DUDESPATROL_PLAYER_H


#include <SFML/Graphics/VertexArray.hpp>

#include "include/Entity.h"
#include "framework/sfmlAddon/AnimatedSprite.h"
#include "World/Level/Elements/Tile.h"

class Player : public Entity{
private:
    const int viewDistance = 128;
    float speed = 34.f;

    sf::Clock frameClock;
    sf::Time deltaTime;

    AnimatedSprite *animatedSprite;
    Animation *animation;
    Animation goingUpAnim;
    Animation goingDownAnim;
    Animation goingLeftAnim;
    Animation goingRightAnim;

    void updateIsoPosition(sf::Vector2f pos);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
    void update(){};

    void setUpAnimations();

public:
    enum Facing{
        UP, DOWN, LEFT, RIGHT
    };

    Player(float x, float y, float width, float height);

    void init();
    void update(std::vector<Renderable *> obstacles);
    void render(sf::RenderWindow *w, Camera *c);
    void movePlayer(Facing direction);

    sf::Vector2f getPosition();

    int getViewDistance();
};


#endif //DUDESPATROL_PLAYER_H
