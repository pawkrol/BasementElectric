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
        sf::Clock effectTimer;
    } be;

    void buffGainEffect();

public:
    LevelEffects(Level *level);

    void update();

    void buffGain(sf::Color color);
};


#endif //DUDESPATROL_LEVELEFFECTS_H
