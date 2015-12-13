//
// Created by pawkrol on 12/2/15.
//

#ifndef DUDESPATROL_MOVEDOWNCOMMAND_H
#define DUDESPATROL_MOVEDOWNCOMMAND_H


#include "Command.h"

class MoveDownCommand : public Command{
public:
    ~MoveDownCommand();
    void execute(Player &player);
};


#endif //DUDESPATROL_MOVEDOWNCOMMAND_H
