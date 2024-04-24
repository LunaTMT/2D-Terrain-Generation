#ifndef STOP_MOVEMENT_COMMANDS_H
#define STOP_MOVEMENT_COMMANDS_H

#include "ICommand.h"
#include "IGameActor.h"

class StopMoveLeftCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class StopMoveRightCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class StopMoveUpCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class StopMoveDownCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

#endif 
