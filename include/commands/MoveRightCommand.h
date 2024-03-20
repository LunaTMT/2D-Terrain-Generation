#ifndef MOVE_RIGHT_COMMAND_H
#define MOVE_RIGHT_COMMAND_H

#include "ICommand.h"

class MoveRightCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_RIGHT_COMMAND_H
