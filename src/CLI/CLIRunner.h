#include "./CLICommandDataCollection.h"
#include "../Command/CommandRecorder.h"

#define MAX_ARGS 10
#define MAX_ARG_LEN 256

typedef struct CLIRunner CLIRunner;

CLIRunner* CLIRunner_new(void* context);
void CLIRunner_destroy(CLIRunner* runner);

int CLIRunner_execute(CLIRunner *self, char** args, int arg_count);
int CLIRunner_listen(CLIRunner *self);
void CLIRunner_stop_listening(CLIRunner* self);

ICommand* CLIRunnerExitCommand_from_args(char** args, int arg_count, void* runner);
