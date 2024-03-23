#include "MoveUpCommand.h"
#include "player.h" 

void MoveUpCommand::execute(Player& player) {
    player.setMovingUp(true);
}
