#ifndef MOVE_LEFT_COMMAND_H
#define MOVE_LEFT_COMMAND_H

#include "ICommand.h"

class MoveLeftCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_LEFT_COMMAND_H
