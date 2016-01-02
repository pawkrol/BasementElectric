//
// Created by pawkrol on 12/2/15.
//

#include "MoveDownCommand.h"

MoveDownCommand::~MoveDownCommand() {

}

void MoveDownCommand::execute(Player &player) {
    player.move(player.DOWN);
}
