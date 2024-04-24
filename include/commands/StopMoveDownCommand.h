#ifndef STOP_MOVE_DOWN_COMMAND_H
#define STOP_MOVE_DOWN_COMMAND_H

#include "ICommand.h"

class StopMoveDownCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_DOWN_COMMAND_H
