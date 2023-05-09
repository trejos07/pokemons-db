#ifndef ICOMMAND_STACK_H
#define ICOMMAND_STACK_H

#include "ICommand.h"

typedef struct CommandStack CommandStack;

CommandStack* CommandStack_new(int history_size);
void CommandStack_destroy(CommandStack* self);
void CommandStack_push(CommandStack* self, ICommand * command);
ICommand* CommandStack_peak(CommandStack* self);
ICommand* CommandStack_pop(CommandStack* self);
void CommandStack_clear(CommandStack* self);

#endif