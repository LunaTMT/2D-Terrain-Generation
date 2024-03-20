#include "MoveDownCommand.h"
#include "player.h" 

void MoveDownCommand::execute(Player& player) {
    player.moveDown();
}
