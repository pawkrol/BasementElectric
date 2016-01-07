//
// Created by pawkrol on 12/4/15.
//

#include "Block.h"
#include "../../../framework/GameWorld.h"

Block::Block(float x, float y) {
    this->x = x;
    this->y = y;

    this->darkness = 50;

    init();
}

void Block::init() {
    texture = GameWorld::wrm->getBlockTexture();

    toIsoCords();
    setPosition(x, y);
    create();
    updateDarkness();
}

void Block::update() {
    setDarkness(defaultDarkness);
}