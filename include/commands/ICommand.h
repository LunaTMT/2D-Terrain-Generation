#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "player.h" // Include the header file for Player class

class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute(Player& player) = 0;
};

#endif // ICOMMAND_H
