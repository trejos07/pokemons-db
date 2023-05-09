#ifndef ICOMMAND_C
#define ICOMMAND_C

#include "./ICommand.h"

struct ICommand {
    void (*execute)(ICommand *);
    void (*un_execute)(ICommand *);
};

void ICommand_execute(ICommand *self)
{
    self->execute(self);
}

void ICommand_un_execute(ICommand *self)
{
    self->un_execute(self);
}

#endif