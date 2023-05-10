#include <stdlib.h>

#ifndef CLICommandData_C
#define CLICommandData_C

#include "../Command/ICommand.h"
#include "CLICommandData.h"

struct CLICommandData {
    int record;
    const char* name;
    const char* help_text;

    ICommand* (*get_command)(char** args, int arg_count, void* runner);
};

CLICommandData* CLICommandData_new(char* name, char* help_text, int record, ICommand* (*get_command)(char** args, int arg_count, void* runner)) 
{
    CLICommandData* command = malloc(sizeof(CLICommandData));
    command->name = name;
    command->help_text = help_text;
    command->record = record;
    command->get_command = get_command;
    return command;
}

#endif