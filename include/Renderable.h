//
// Created by pawkrol on 11/27/15.
//

#ifndef DUDESPATROL_RENDERELEMENT_H
#define DUDESPATROL_RENDERELEMENT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../framework/Camera.h"

class Entity;
class GameWorld;

class Renderable : public sf::Drawable, public sf::Transformable{
protected:
    sf::Texture *texture;

public:
    float x;
    float y;

    float width;
    float height;

    float x_offset = 0;
    float y_offset = 0;

    bool collidable = true;
    bool collectable = false;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow *w, Camera *c) = 0;
    virtual void toIsoCords(){
        float tx = x;
        x = (x - y);
        y = (tx + y)/2;
    }
    virtual void toCarCords(){
        float tx = x;
        x = (x + 2*y)/2;
        y = (2*y - tx)/2;
    }

    virtual void manageCollectableFor(GameWorld*, Entity *entity){};
};


#endif //DUDESPATROL_RENDERELEMENT_H
