//
// Created by pawkrol on 1/1/16.
//

#ifndef DUDESPATROL_MOBAI_H
#define DUDESPATROL_MOBAI_H


#include "Player.h"

class MobAI {
private:
    Entity *mob;
    sf::Clock ticker;

    int dir;
    int sign;

    std::vector<Renderable *> getMobObstacles(GameWorld *);

public:
    MobAI(Entity *mob);

    sf::Vector2f getMoveTo(GameWorld *, float deltaTime);
};


#endif //DUDESPATROL_MOBAI_H
