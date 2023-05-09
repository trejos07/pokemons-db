#include "../PokemonDB.h"
#include "../../Command/ICommand.h"
#include "../../CLI/CLIRunner.h"

typedef struct PokemonDBShowCommand PokemonDBShowCommand;

void PokemonDBShowCommand_execute(ICommand* command);
void PokemonDBShowCommand_un_execute(ICommand* command);
PokemonDBShowCommand* PokemonDBShowCommand_new(PokemonDB* pokemonDB, char* toShow);
ICommand* PokemonDBShowCommand_from_args(char** args, int arg_count, void* runner);
