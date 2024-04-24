#include "MovementCommands.h"
#include "IGameActor.h" 


void MoveLeftCommand::execute(IGameActor& actor) {
    actor.setMovingLeft(true);
}

void MoveRightCommand::execute(IGameActor& actor) {
    actor.setMovingRight(true);
}

void MoveUpCommand::execute(IGameActor& actor) {
    actor.setMovingUp(true);
}

void MoveDownCommand::execute(IGameActor& actor) {
    actor.setMovingDown(true);
}
