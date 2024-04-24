#ifndef MOVEMENT_COMMANDS_H
#define MOVEMENT_COMMANDS_H

#include "ICommand.h"
#include "IGameActor.h"

class MoveLeftCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class MoveRightCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class MoveUpCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

class MoveDownCommand : public ICommand {
public:
    virtual void execute(IGameActor& actor) override;
};

#endif
