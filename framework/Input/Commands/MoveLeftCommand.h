//
// Created by pawkrol on 12/3/15.
//

#ifndef DUDESPATROL_MOVELEFTCOMMAND_H
#define DUDESPATROL_MOVELEFTCOMMAND_H

#include "Command.h"

class MoveLeftCommand : public Command {
public:
    ~MoveLeftCommand();
    void execute(Player &player);
};


#endif //DUDESPATROL_MOVELEFTCOMMAND_H
