//
// Created by pawkrol on 1/5/16.
//

#ifndef DUDESPATROL_ACTIONCOMMAND_H
#define DUDESPATROL_ACTIONCOMMAND_H


#include "Command.h"

class ActionCommand : public Command{

public:
    void execute(Player &player);
};


#endif //DUDESPATROL_ACTIONCOMMAND_H
