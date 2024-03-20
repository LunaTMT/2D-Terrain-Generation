#include "MoveLeftCommand.h"
#include "player.h" 

void MoveLeftCommand::execute(Player& player) {
    player.moveLeft();
}
