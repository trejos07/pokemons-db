#ifndef CLICommandData_H
#define CLICommandData_H

#include "../Command/ICommand.h"

typedef struct CLICommandData CLICommandData;

CLICommandData* CLICommandData_new(char* name, char* help_text, int record, ICommand* (*get_command)(char** args, int arg_count, void* context));

#endif