#include "StopMoveDownCommand.h"
#include "player.h"

void StopMoveDownCommand::execute(Player& player) {
    player.setMovingDown(false);
}
