#include <stdlib.h>
#include <string.h>

#include "CLICommandDataCollection.h"
#include "CLICommandData.c"

struct CLICommandDataCollection {
    CLICommandData** commands;
    int commandsCount;
};

CLICommandDataCollection* CLICommandDataCollection_new() 
{
    CLICommandDataCollection* list = malloc(sizeof(CLICommandDataCollection));
    list->commandsCount = 0;
    list->commands = malloc(sizeof(CLICommandData*) * COMMAND_LIST_CAPACITY);
    return list;
}

void CLICommandDataCollection_destroy(CLICommandDataCollection* self) 
{
    free(self->commands);
    free(self);
}

void CLICommandDataCollection_add(CLICommandDataCollection* self, CLICommandData* command) 
{
    if (self->commandsCount >= COMMAND_LIST_CAPACITY) {
        return;
    }
    
    self->commands[self->commandsCount] = command;
    self->commandsCount++;
}

CLICommandData* CLICommandDataCollection_find_by_name(CLICommandDataCollection *self, const char* name) 
{
    for (int i = 0; i < self->commandsCount; i++) {
        if (strcmp(self->commands[i]->name, name) == 0) {
            return self->commands[i];
        }
    }
    return NULL;
}