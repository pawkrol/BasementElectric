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

class Renderable : public sf::Drawable, public sf::Transformable{
protected:
    sf::Texture texture;

public:
    float x;
    float y;

    float width;
    float height;

    bool collidable = true;

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

};


#endif //DUDESPATROL_RENDERELEMENT_H
