#include "StopMoveUpCommand.h"
#include "player.h"

void StopMoveUpCommand::execute(Player& player) {
    player.setMovingUp(false);
}
