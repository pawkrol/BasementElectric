//
// Created by pawkrol on 12/3/15.
//

#include "MoveLeftCommand.h"

MoveLeftCommand::~MoveLeftCommand() { }

void MoveLeftCommand::execute(Player &player) {
    player.move(player.LEFT);
}
