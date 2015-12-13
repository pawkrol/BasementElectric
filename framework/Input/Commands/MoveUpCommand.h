//
// Created by pawkrol on 12/1/15.
//

#ifndef DUDESPATROL_MOVEUPCOMMAND_H
#define DUDESPATROL_MOVEUPCOMMAND_H

#include "Command.h"

class MoveUpCommand : public Command{
public:
    ~MoveUpCommand();
    void execute(Player &player);
};


#endif //DUDESPATROL_MOVEUPCOMMAND_H
