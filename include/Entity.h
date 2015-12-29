//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_ENTITY_H
#define DUDESPATROL_ENTITY_H

#include "../include/Renderable.h"

class Entity : public Renderable{
protected:
    float speed = 0.83;
    sf::Vector2f moveVector;

    bool checkCollision(std::vector<Renderable *> obstacles){
        for (Renderable *o: obstacles){
            o->toCarCords();
            toCarCords();

            bool collide = o->x + o->width/2 < moveVector.x + width &&
                           o->x + o->width/3 > moveVector.x &&
                           o->y + o->width/2 < moveVector.y + height &&
                           o->y + o->height/3 > moveVector.y;

            o->toIsoCords();
            toIsoCords();

            if (collide){
                return collide;
            }
        }

        return false;
    }

public:
    virtual void update(std::vector<Renderable *> obstacles) = 0;

    virtual ~Entity(){};
};


#endif //DUDESPATROL_ENTITY_H
