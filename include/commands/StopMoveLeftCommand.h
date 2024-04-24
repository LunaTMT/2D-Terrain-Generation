#ifndef STOP_MOVE_LEFT_COMMAND_H
#define STOP_MOVE_LEFT_COMMAND_H

#include "ICommand.h"

class StopMoveLeftCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_LEFT_COMMAND_H
