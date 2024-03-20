#include "MoveRightCommand.h"
#include "player.h" 

void MoveRightCommand::execute(Player& player) {
    player.moveRight();
}
