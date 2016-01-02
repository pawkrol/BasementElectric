//
// Created by pawkrol on 12/1/15.
//

#include "MoveUpCommand.h"

MoveUpCommand::~MoveUpCommand() {

}

void MoveUpCommand::execute(Player &player) {
    player.move(player.UP);
}
