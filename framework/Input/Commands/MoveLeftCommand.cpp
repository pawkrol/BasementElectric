//
// Created by pawkrol on 12/3/15.
//

#include "MoveLeftCommand.h"

MoveLeftCommand::~MoveLeftCommand() { }

void MoveLeftCommand::execute(Player &player) {
    player.toCarCords();
    player.x -= player.getSpeed();
    player.setFacing(player.LEFT);
    player.toIsoCords();
}
