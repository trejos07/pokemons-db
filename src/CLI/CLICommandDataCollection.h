#include "./CLICommandData.h"

#define COMMAND_LIST_CAPACITY 32

typedef struct CLICommandDataCollection CLICommandDataCollection;

CLICommandDataCollection* CLICommandDataCollection_new();
void CLICommandDataCollection_destroy(CLICommandDataCollection* self);

void CLICommandDataCollection_add(CLICommandDataCollection* self, CLICommandData* command);
CLICommandData* CLICommandDataCollection_find_by_name(CLICommandDataCollection *self, const char* name);
