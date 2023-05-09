#include <stdlib.h> 
#include <stdio.h> 

#ifndef ICOMMAND_STACK_C
#define ICOMMAND_STACK_C

#include "CommandStack.h"

struct CommandStack {
    ICommand** commands;
    int history_size;
    int count;
};

CommandStack* CommandStack_new(int history_size)
{
    CommandStack* stack = malloc(sizeof(CommandStack));

    if (stack == NULL) {
        printf("Error: Failed to allocate memory for CommandStack.\n");
        return NULL;
    }

    stack->count = 0;
    stack->history_size = history_size;
    stack->commands = calloc(stack->history_size, sizeof(ICommand*));

    if (stack->commands == NULL) {
        printf("Error: Failed to allocate memory for commands array in CommandStack.\n");
        return NULL;
    }

    return stack;
}

void CommandStack_destroy(CommandStack* self)
{
    free(self->commands);
    free(self);
}

void CommandStack_push(CommandStack* self, ICommand * command)
{
    char overflow = self->count >= self->history_size;

    if (overflow) {
        // Shift the elements to the left to make a gap at the end the new element
        for (int i = 0; i < self->count - 1; i++) {
            self->commands[i] = self->commands[i+1];
        }
    }

    self->commands[self->count] = command;

    if (!overflow) {
        self->count++;
    }
}

ICommand* CommandStack_peak(CommandStack* self)
{
    return self->commands[self->count - 1];
}

ICommand* CommandStack_pop(CommandStack* self)
{
    if (self->count == 0) {
        return NULL;
    }

    ICommand* last = self->commands[self->count - 1];
    self->commands[self->count - 1] = NULL;
    self->count--;
    return last;
}

void CommandStack_clear(CommandStack* self)
{
    for (int i = 0; i < self->count; i++) {
        self->commands[i] = NULL;
    }

    self->count = 0;
}

#endif