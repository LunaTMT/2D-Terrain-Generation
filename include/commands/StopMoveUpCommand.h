#ifndef STOP_MOVE_UP_COMMAND_H
#define STOP_MOVE_UP_COMMAND_H

#include "ICommand.h"

class StopMoveUpCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_UP_COMMAND_H
