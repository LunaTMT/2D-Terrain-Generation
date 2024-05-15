#include "MovementCommands.h"
#include "IGameActor.h" 


void MoveLeftCommand::execute(IGameActor& actor) {
    std::cout << "left";
    actor.setMovingLeft(true);
}

void MoveRightCommand::execute(IGameActor& actor) {
    std::cout << "right";
    actor.setMovingRight(true);
}

void MoveUpCommand::execute(IGameActor& actor) {
    std::cout << "up";
    actor.setMovingUp(true);
}

void MoveDownCommand::execute(IGameActor& actor) {
    std::cout << "down";
    actor.setMovingDown(true);
}
