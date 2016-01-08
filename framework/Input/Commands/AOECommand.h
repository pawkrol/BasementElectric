//
// Created by pawkrol on 1/8/16.
//

#ifndef DUDESPATROL_AOECOMMAND_H
#define DUDESPATROL_AOECOMMAND_H


#include "Command.h"

class AOECommand : public Command{
public:
    void execute(Player &player);
};


#endif //DUDESPATROL_AOECOMMAND_H
