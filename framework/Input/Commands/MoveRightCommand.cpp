//
// Created by pawkrol on 12/3/15.
//

#include "MoveRightCommand.h"

MoveRightCommand::~MoveRightCommand() { }

void MoveRightCommand::execute(Player &player) {
    player.move(player.RIGHT);
}
