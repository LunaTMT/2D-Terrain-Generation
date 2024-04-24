#ifndef STOP_MOVE_RIGHT_COMMAND_H
#define STOP_MOVE_RIGHT_COMMAND_H

#include "ICommand.h"

class StopMoveRightCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_RIGHT_COMMAND_H
