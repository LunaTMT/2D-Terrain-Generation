#include "StopMovementCommands.h"
#include "IGameActor.h"

void StopMoveLeftCommand::execute(IGameActor& actor) {
    actor.setMovingLeft(false);
}

void StopMoveRightCommand::execute(IGameActor& actor) {
    actor.setMovingRight(false);
}

void StopMoveUpCommand::execute(IGameActor& actor) {
    actor.setMovingUp(false);
}

void StopMoveDownCommand::execute(IGameActor& actor) {
    actor.setMovingDown(false);
}
