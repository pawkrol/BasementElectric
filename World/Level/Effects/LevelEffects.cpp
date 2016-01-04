//
// Created by pawkrol on 1/4/16.
//

#include "LevelEffects.h"
#include "../Lights/LightSource.h"

LevelEffects::LevelEffects(Level *level) {
    this->level = level;
    c_effect = NONE;
}

void LevelEffects::update() {
    levelSize = level->getSize();

    switch (c_effect){
        case BUFF_EF:
            buffGainEffect();
            break;

        case NONE:
            break;
    }
}

void LevelEffects::buffGainEffect() {
    if (effectTimer.getElapsedTime() >= sf::seconds(.00001f)){
        if (!be.xGone) {
            for (int x = 0; x < levelSize.x; x++) {
                if ((*level)(0, x + be.buff_y * levelSize.x) != nullptr) {
                    (*level)(0, x + be.buff_y * levelSize.x)->setColor(be.buffGainColor);
                };
                if ((*level)(1, x + be.buff_y * levelSize.x) != nullptr) {
                    (*level)(1, x + be.buff_y * levelSize.x)->setColor(be.buffGainColor);
                };
            }
            be.buff_y++;

            if (be.buff_y == levelSize.y) {
                be.xGone = true;
            }
        } else {
            for (int y = 0; y < levelSize.x; y++) {
                if ((*level)(0, be.buff_x + y * levelSize.x) != nullptr) {
                    (*level)(0, be.buff_x + y * levelSize.x)->setColor(be.buffGainColor);
                };

                if ((*level)(1, be.buff_x + y * levelSize.x) != nullptr) {
                    (*level)(1, be.buff_x + y * levelSize.x)->setColor(be.buffGainColor);
                };
            }
            be.buff_x++;

            if (be.buff_x == levelSize.y) {
                be.yGone = true;
            }
        }

        effectTimer.restart();
    }

    if (be.yGone && be.buff_y == levelSize.y){
        be.xGone = false;
        be.yGone = false;

        level->getLightSource()->setShining(true);
        c_effect = NONE;
    }
}

void LevelEffects::buffGain(sf::Color color) {
    be.buffGainColor = color;

    if (c_effect != BUFF_EF){
        level->getLightSource()->setShining(false);

        effectTimer.restart();
        be.buff_y = 0;
        be.buff_x = 0;
        c_effect = BUFF_EF;
    }
}
