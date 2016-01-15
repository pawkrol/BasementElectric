//
// Created by pawkrol on 1/5/16.
//

#ifndef DUDESPATROL_DOORS_H
#define DUDESPATROL_DOORS_H


#include "../../../framework/sfmlAddon/AnimatedSprite.h"
#include "Tile.h"

class Doors : public Tile{
private:
    AnimatedSprite *sprite;
    Animation anim;

    sf::Clock frameClock;
    sf::Time frameTime;

    bool isClosed = true;

    void updateDarkness();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const{};

public:
    enum Side {
        DOWN = 1, UP = 2, LEFT = 3, RIGHT = 4
    };
    Side _side;

    int id = 0;

    Doors(float x, float y, Side side, bool isClosed, int id = 0);

    void init();
    void update();
    void render(sf::RenderWindow *w, Camera *c);

    void setDarkness(sf::Uint8 darkness);

    void setClosed(bool isClosed);
    bool getClosed();

    ~Doors();
};


#endif //DUDESPATROL_DOORS_H
