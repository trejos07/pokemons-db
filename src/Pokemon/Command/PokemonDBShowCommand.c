#include <stdlib.h>

#ifndef PokemonDBShowCommand_C
#define PokemonDBShowCommand_C

#include "PokemonDBShowCommand.h"
#include "../../Command/ICommand.c"
#include "../PokemonDB.c"
#include "../../CLI/CLIRunner.c"

struct PokemonDBShowCommand {
    ICommand base;
    PokemonDB* pokemonDB;
    char* toShow;
};

void PokemonDBShowCommand_execute(ICommand* command)
{
    PokemonDBShowCommand* self = (PokemonDBShowCommand*) command;

    if (strcmp(self->toShow, "search") == 0) {
        PokemonList_print_as_table(self->pokemonDB->query_result, -1);
        return;
    }

    Pokemon** p = PokemonDB_find_pokemon_by_field(self->pokemonDB, "ID", self->toShow);
    Pokemon_print_multi_line(*p);
}

void PokemonDBShowCommand_un_execute(ICommand* command)
{
    printf("undo show command");
}

PokemonDBShowCommand* PokemonDBShowCommand_new(PokemonDB* pokemonDB, char* toShow)
{
    PokemonDBShowCommand* command = malloc(sizeof(PokemonDBShowCommand));
    command->pokemonDB = pokemonDB;
    command->toShow = toShow;
    command->base.execute = PokemonDBShowCommand_execute;
    command->base.un_execute = PokemonDBShowCommand_un_execute;
    return command;
}

ICommand* PokemonDBShowCommand_from_args(char** args, int arg_count, void* runner)
{
    if (arg_count < 2) {
        printf("Error: Missing argument. Usage:\n  - show <id>: gets the entry with the given id.\n  - show search: gets the last query results.\n");
        return NULL;
    }

    CLIRunner* runnerp = (CLIRunner*) runner;
    PokemonDB* db = (PokemonDB*) runnerp->context;
    return &PokemonDBShowCommand_new(db, args[0])->base;
}

#endif