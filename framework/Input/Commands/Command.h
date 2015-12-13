//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_COMMAND_H
#define DUDESPATROL_COMMAND_H


#include "../../../Player.h"

class Command {
public:
    virtual void execute(Player &player) = 0;
};


#endif //DUDESPATROL_COMMAND_H
