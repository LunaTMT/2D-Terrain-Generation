#ifndef MOVE_UP_COMMAND_H
#define MOVE_UP_COMMAND_H

#include "ICommand.h"

class MoveUpCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_UP_COMMAND_H
