//
// Created by pawkrol on 12/3/15.
//

#include "MoveRightCommand.h"

MoveRightCommand::~MoveRightCommand() { }

void MoveRightCommand::execute(Player &player) {
    player.toCarCords();
    player.x += player.getSpeed();
    player.setFacing(player.RIGHT);
    player.toIsoCords();
}
