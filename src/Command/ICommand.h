#ifndef ICOMMAND_H
#define ICOMMAND_H

typedef struct ICommand ICommand;

void ICommand_execute(ICommand *self);
void ICommand_un_execute(ICommand *self);

#endif // ICOMMAND_H