//
// Created by pawkrol on 1/4/16.
//

#ifndef DUDESPATROL_LEVELEFFECTS_H
#define DUDESPATROL_LEVELEFFECTS_H


#include "../Level.h"

class LevelEffects {
private:
    Level *level;
    sf::Vector2i levelSize;

    sf::Clock effectTimer;

    enum Effect{
        NONE, BUFF_EF
    };
    Effect c_effect;

    struct BuffEffect {
        int buff_y;
        int buff_x;

        bool xGone = false;
        bool yGone = false;

        sf::Color buffGainColor;
    } be;

    struct SpawnerEffect {
        
        sf::Color spawnerDeadColor;
    } se;

    void buffGainEffect();

public:
    LevelEffects(Level *level);

    void update();

    void buffGain(sf::Color color);

    void spawnerDead(sf::Color color);
};


#endif //DUDESPATROL_LEVELEFFECTS_H
