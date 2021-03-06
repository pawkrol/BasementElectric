//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_COMMAND_H
#define DUDESPATROL_COMMAND_H


#include "../../../World/Player.h"

class Command {
public:
    virtual void execute(Player &player) = 0;

    virtual ~Command(){ };
};


#endif //DUDESPATROL_COMMAND_H
