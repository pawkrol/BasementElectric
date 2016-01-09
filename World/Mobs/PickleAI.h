//
// Created by pawkrol on 1/8/16.
//

#ifndef DUDESPATROL_PICKLEAI_H
#define DUDESPATROL_PICKLEAI_H


#include "../../framework/GameWorld.h"
#include "MadPickle.h"

class PickleAI {
private:
    MadPickle *mob;
    sf::Clock ticker;

    int dir;
    int sign;

    std::vector<Renderable *> getMobObstacles(GameWorld *);

public:
    PickleAI(MadPickle *mob);

    sf::Vector2f getMoveTo(GameWorld *, float deltaTime);
};


#endif //DUDESPATROL_PICKLEAI_H
