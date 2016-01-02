//
// Created by pawkrol on 12/29/15.
//

#ifndef DUDESPATROL_HITCOMMAND_H
#define DUDESPATROL_HITCOMMAND_H


#include "Command.h"

class HitCommand : public Command{

public:
    virtual void execute(Player &player) override;
};


#endif //DUDESPATROL_HITCOMMAND_H
