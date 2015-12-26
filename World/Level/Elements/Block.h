//
// Created by pawkrol on 12/4/15.
//

#ifndef DUDESPATROL_BLOCK_H
#define DUDESPATROL_BLOCK_H

#include "Tile.h"

class Block : public Tile{
public:
    Block(float x, float y);

    void init();
    void update();
};


#endif //DUDESPATROL_BLOCK_H
