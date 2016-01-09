//
// Created by pawkrol on 1/1/16.
//

#ifndef DUDESPATROL_MOBAI_H
#define DUDESPATROL_MOBAI_H


#include "../Player.h"
#include "Rat.h"

class RatAI {
private:
    Rat *mob;
    sf::Clock ticker;

    int dir;
    int sign;

    std::vector<Renderable *> getMobObstacles(GameWorld *);

public:
    RatAI(Rat* mob);

    sf::Vector2f getMoveTo(GameWorld *, float deltaTime);
};


#endif //DUDESPATROL_MOBAI_H
