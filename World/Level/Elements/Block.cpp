//
// Created by pawkrol on 12/4/15.
//

#include <iostream>
#include "Block.h"

Block::Block(float x, float y) {
    this->x = x;
    this->y = y;
    this->darkness = 50;

    init();
}

void Block::init() {
    if (!texture.loadFromFile("res/block.png")){
        std::cout << "CAN'T LOAD BLOCK TEXTURE" << std::endl;
    }

    toIsoCords();
    setPosition(x, y);
    create();
    updateDarkness();
}

void Block::update() {
    setDarkness(_defaultDarkness);
}