//
// Created by pawkrol on 12/3/15.
//

#ifndef DUDESPATROL_MOVERIGHTCOMMAND_H
#define DUDESPATROL_MOVERIGHTCOMMAND_H


#include "Command.h"

class MoveRightCommand : public Command{
public:
    ~MoveRightCommand();
    void execute(Player &player);
};


#endif //DUDESPATROL_MOVERIGHTCOMMAND_H
