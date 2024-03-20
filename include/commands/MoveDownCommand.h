#ifndef MOVE_DOWN_COMMAND_H
#define MOVE_DOWN_COMMAND_H

#include "ICommand.h"

class MoveDownCommand : public ICommand {
public:
    virtual void execute(Player& player) override;
};

#endif // MOVE_DOWN_COMMAND_H
