//
// Created by pawkrol on 12/1/15.
//

#include "MoveUpCommand.h"

MoveUpCommand::~MoveUpCommand() {

}

void MoveUpCommand::execute(Player &player) {
    player.toCarCords();
    player.y -= player.getSpeed();
    player.setFacing(player.UP);
    player.toIsoCords();
}
