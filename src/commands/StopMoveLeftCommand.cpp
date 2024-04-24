#include "StopMoveLeftCommand.h"
#include "player.h"

void StopMoveLeftCommand::execute(Player& player) {
    player.setMovingLeft(false);
}
