#include "StopMoveRightCommand.h"
#include "player.h"

void StopMoveRightCommand::execute(Player& player) {
    player.setMovingRight(false);
}
