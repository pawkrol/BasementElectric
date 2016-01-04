//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_ENTITY_H
#define DUDESPATROL_ENTITY_H

#include "Renderable.h"

class Entity : public Renderable{
protected:
    float fullHP = 20.f;
    float fullStamina = 20.f;

    float speed = 22.f;
    float hp = fullHP;
    float stamina = fullStamina;

    sf::Vector2f moveVector;

    virtual void die(GameWorld*) = 0;
public:
    enum Facing{
        UP, DOWN, LEFT, RIGHT
    };

    Facing _facing;

    bool isMovable = true;

    virtual bool checkCollision(std::vector<Renderable*> obstacles){
        for (Renderable *o: obstacles){
            if (!o->collidable) continue;

            if (checkCollision(o)) {
                if (o->collectable) {
                    continue;
                }

                return true;
            }
        }

        return false;
    }

    bool checkCollision(Renderable* o){
        o->toCarCords();
        toCarCords();

        bool collide = o->x + o->width/2 + o->x_offset < moveVector.x + width &&
                       o->x + o->width/3 > moveVector.x &&
                       o->y + o->height/2 + o->y_offset < moveVector.y + height &&
                       o->y + o->height/3 > moveVector.y;

        o->toIsoCords();
        toIsoCords();

        return collide;
    }

    virtual float getFullHP(){
        return fullHP;
    }

    virtual float getFullStamina(){
        return fullStamina;
    }

    virtual float getHP(){
        return hp;
    }

    virtual void setHP(float hp){
        if (this->hp < fullHP) {
            if (hp > fullHP) {
                this->hp = fullHP;
            } else {
                this->hp = hp;
            }
        }
    }

    virtual float getStamina(){
        return stamina;
    }

    virtual void setStamina(float stamina){
        if (this->stamina < fullStamina) {
            if (stamina > fullStamina){
                this->stamina = fullStamina;
            } else {
                this->stamina = stamina;
            }
        }
    }

    virtual float getSpeed(){
        return speed;
    }

    virtual void update(GameWorld *) = 0;
    virtual void takeDamage(float damage) = 0;
    virtual ~Entity(){};
};


#endif //DUDESPATROL_ENTITY_H
