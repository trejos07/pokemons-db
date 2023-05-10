#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CLIRunner_C
#define CLIRunner_C

#include "CLIRunner.h"
#include "CLICommandData.c"
#include "CLICommandDataCollection.h"
#include "../Command/ICommand.c"
#include "../Command/CommandRecorder.h"

struct CLIRunner {
    CLICommandDataCollection* knownCommands;
    CommandRecorder* commandRecorder;
    void* context;
    char* prompt;
    int listening;

};

CLIRunner* CLIRunner_new(void* context) 
{
    CLIRunner* runner = malloc(sizeof(CLIRunner));
    
    if (runner == NULL) {
        printf("Error: Failed to allocate memory for CLIRunner.\n");
        return NULL;
    }

    runner->commandRecorder = CommandRecorder_new(5);
    runner->knownCommands = CLICommandDataCollection_new();
    runner->context = context;
    return runner;
}

void CLIRunner_destroy(CLIRunner* runner) 
{
    CommandRecorder_destroy(runner->commandRecorder);
    CLICommandDataCollection_destroy(runner->knownCommands);
    free(runner);
}

int CLIRunner_execute(CLIRunner *self, char** args, int arg_count) 
{
    if (arg_count < 1) {
        return 0;
    }

    CLICommandData* commandData = CLICommandDataCollection_find_by_name(self->knownCommands, args[0]);

    if (commandData == NULL) {
        printf("Error: unknown command '%s'\n", args[0]);
        return 0;
    }

    ICommand* command = commandData->get_command(args, arg_count, self);

    if (command == NULL) {
        return 0;
    }

    command->execute(command);

    if (commandData->record) {
        CommandRecorder_record(self->commandRecorder, command);
    }

    return 1;
}

void print_args(char** args, int argc)
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("args[%d] = %s\n", i, args[i]);
    }
}

char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (len > n) {
        len = n;
    }
    char *new = malloc(len + 1);
    if (new == NULL) {
        return NULL;
    }
    memcpy(new, s, len);
    new[len] = '\0';
    return new;
}

int parse_args(char *line, int max_args, char *argv[]) {
    int argc = 0; //args count
    char arg[MAX_ARG_LEN]; //arg
    char *p = line;
    char *q = arg;
    int in_quote = 0;
    int in_escape = 0;

    // Parse the input string
    while (*p != '\0' && argc < max_args) {
        if (*p == '\\' && !in_escape) {
            // Handle escape sequence
            in_escape = 1;
        } else if (*p == '"' && !in_escape) {
            // Handle quoted string
            in_quote = !in_quote;
        } else if ((*p == ' ' || *p == '\t' || *p == '\n') && !in_quote) {
            // End of argument
            if (q > arg) {
                // Add the argument to argv
                *q = '\0';
                argv[argc] = strndup(arg, MAX_ARG_LEN);
                argc++;
                q = arg;
            }
        } else {
            // Add character to argument
            *q = *p;
            q++;
        }

        // Reset escape sequence flag
        in_escape = 0;

        // Move to the next character
        p++;
    }

    // Add the last argument, if any
    if (q > arg) {
        *q = '\0';
        argv[argc] = strndup(arg, MAX_ARG_LEN);
        argc++;
    }

    // Add a NULL terminator at the end of the argv array
    argv[argc] = NULL;

    return argc;
}

int CLIRunner_listen(CLIRunner *self)
{
    self->listening = 1;

    char line[1024];
    char *argv[MAX_ARGS];
    int argc = 0;

    while (self->listening) {
        printf("Enter command: "); //print text requesting user input 

        if (fgets(line, sizeof(line), stdin) == NULL) { // if no input just continue waiting
            continue;
        }

        argc = parse_args(line, MAX_ARGS, argv); // Parse the line into argc/argv
        print_args(argv, argc); // Print the arguments

        CLIRunner_execute(self, argv, argc);
    }

    // Free the memory used by the argv array
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }

    return 0;
}

void CLIRunner_stop_listening(CLIRunner* self)
{
    self->listening = 0;
}

ICommand* CLIRunnerExitCommand_from_args(char** args, int arg_count, void* runner)
{   
    CLIRunner_stop_listening((CLIRunner*) runner);
    return NULL;
}

#endif