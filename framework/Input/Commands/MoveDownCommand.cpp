//
// Created by pawkrol on 12/2/15.
//

#include "MoveDownCommand.h"

MoveDownCommand::~MoveDownCommand() {

}

void MoveDownCommand::execute(Player &player) {
    player.toCarCords();
    player.y += player.getSpeed();
    player.setFacing(player.DOWN);
    player.toIsoCords();
}
