#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "IGameActor.h" // Include the header file for Player class

class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute(IGameActor& actor) = 0;
};

#endif // ICOMMAND_H
