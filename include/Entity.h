//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_ENTITY_H
#define DUDESPATROL_ENTITY_H

#include "Renderable.h"

class GameWorld;

class Entity : public Renderable{
protected:
    sf::Vector2f moveVector;

    virtual void die(GameWorld*) = 0;

public:
    enum Facing{
        UP, DOWN, LEFT, RIGHT
    };
    Facing _facing;

    float speed = 22.f;
    float hp = 20.f;

    bool isMovable = true;

    bool checkCollision(std::vector<Renderable*> obstacles){
        for (Renderable *o: obstacles){
            if (!o->collidable) continue;

            if (checkCollision(o))
                return true;
        }

        return false;
    }

    bool checkCollision(Renderable* o){
        o->toCarCords();
        toCarCords();

        bool collide = o->x + o->width/2 < moveVector.x + width &&
                       o->x + o->width/3 > moveVector.x &&
                       o->y + o->height/2 < moveVector.y + height &&
                       o->y + o->height/3 > moveVector.y;

        o->toIsoCords();
        toIsoCords();

        return collide;
    }

    virtual void update(GameWorld *) = 0;
    virtual void takeDamage(float damage) = 0;
    virtual ~Entity(){};
};


#endif //DUDESPATROL_ENTITY_H
